---
name: openssh-client-config
id: LM-OPENSSH-CLIENT-CONFIG
kind: law-mold
description: >
  Portable law mold for commenting unsupported keywords in the OpenSSH client
  config. OS class selects the keyword family. Add, update, and review share
  one render. Cite as LM-OPENSSH-CLIENT-CONFIG. Sample code lives here.
---

**file**: template-openssh-client-config.md  
**Mold-ID**: LM-OPENSSH-CLIENT-CONFIG  
**Status**: Active (Version 1.0.0)  
**Project**: Any CIAO-Lite Project (reusable template)  
**Philosophy**: CIAO / CIAO-Lite (Caution • Intentional • Anti-fragile • Over-engineered / Over-protect)

**Folder structure (policy):** [`docs/policies/policy-docs-folder-structure.md`](../../policies/policy-docs-folder-structure.md). This file is a **law mold** under `docs/templates/requirements/`.

# Template: OpenSSH client config — unsupported parameters

## 1. Purpose

Portable law for an **active** keyword in `{{HOME}}/.ssh/config` that this OpenSSH build rejects.

| Idea | Rule |
|------|------|
| Active line | First non-space character is not `#` |
| Unsupported parameter | That build prints an unsupported-option error for the keyword |
| Remedy | Comment the line in place. Keep the indent and the keyword text |
| Not this mold | Deposit / sync of the file (**`LM-SHELL-CONFIG-BACKUP`**). Server `sshd` file. Private keys |

Specialize the OS table into the product domain requirement. **This mold is not product law.**

## 2. Terminologies

| Term | Role |
|------|------|
| **OpenSSH** | Client that reads `{{HOME}}/.ssh/config`, and the server program `sshd` |
| **Unsupported parameter in the config file** | Active keyword this build rejects. A leading `#` is ignored |

**Policies:** `docs/policies/policy-no-hardcode.md` · **`PO-NON-EXPOSE-LOCAL-MACHINE`**

## 3. Core rules (portable)

### 3.1 OS class

| Class | Comment these active keywords |
|-------|-------------------------------|
| `alpine` | keyword name starts with `GSSAPI` |
| `termux` | `HostKeyAlgorithms`, `PubkeyAcceptedAlgorithms`, `PubkeyAcceptedKeyTypes` |
| `posix` | none of those families |

Detect order when no override is set: Termux userspace wins, then `ID` / `ID_LIKE` containing `alpine`, else `posix`. An explicit class name (`alpine`, `termux`, `posix`) wins over detect. Do not invent a Dropbear, OpenWrt, or Windows row here.

### 3.2 Add, update, review

| Moment | Behavior |
|--------|----------|
| **Add** | A rewrite that inserts a stanza comments unsupported keywords already in the file, and writes a new rejected keyword as a comment |
| **Update** | A rewrite that changes a stanza uses the same comment render. It does not resurrect an active rejected keyword |
| **Review** | The typed verb renders the chosen file. A show of a stanza still treats a commented algorithm keyword as present |

### 3.3 Verb and automatic pass

Typed verb (Latin token `fix-config`). Flags follow the verb.

| Flags | Read | Write |
|-------|------|-------|
| none | `{{HOME}}/.ssh/config` | that file |
| `--input-file PATH` | `PATH` | that file |
| `--output-file PATH` | `{{HOME}}/.ssh/config` | `PATH` |
| both | input path | output path; input stays |

Every process start runs the same render against `{{HOME}}/.ssh/config` before dispatch, including a zero-argument start. Missing, unreadable, or unwritable is a silent no-op. Identical text is a no-op. A real change keeps a rolling `config.fix-config.bak` (mode **600**) and replaces the file (mode **600**) with no user-visible line. The automatic pass does not create the file when it is absent. Explicit in-place change may use the product’s dated backup. Explicit JSON is one object. Quiet explicit output has no human line.

**MUST NOT** number this verb on a TTY menu. **MUST NOT** put the flags before the verb.

## 4. Sample code

```sh
# {{APP_NAME}} — comment unsupported OpenSSH client keywords.
# os is alpine, termux, or posix. Paths use {{HOME}}.

fix_os_class() {
    case "${CLI_OS-}" in
        alpine|termux|posix) printf '%s' "${CLI_OS}"; return 0 ;;
    esac
    printf '%s' posix
}

fix_config_render() {
    _src="$1"
    _dst="$2"
    _os=$(fix_os_class)
    awk -v os="${_os}" '
        function unsupported(k) {
            if (os == "alpine" && k ~ /^gssapi/) return 1
            if (os == "termux" && (k == "hostkeyalgorithms" || k == "pubkeyacceptedalgorithms" || k == "pubkeyacceptedkeytypes")) return 1
            return 0
        }
        {
            line = $0
            indent = ""
            rest = line
            if (match(line, /^[[:space:]]*/)) {
                indent = substr(line, 1, RLENGTH)
                rest = substr(line, RLENGTH + 1)
            }
            if (rest == "" || substr(rest, 1, 1) == "#") { print line; next }
            if (match(rest, /^[A-Za-z][A-Za-z0-9]*/)) {
                k = tolower(substr(rest, RSTART, RLENGTH))
                if (unsupported(k)) { print indent "# " rest; next }
            }
            print line
        }
    ' "${_src}" > "${_dst}"
}

# Automatic pass. Silent. No-op when {{HOME}}/.ssh/config is missing.
fix_config_auto() {
    _cfg="${HOME}/.ssh/config"
    [ -f "${_cfg}" ] && [ -r "${_cfg}" ] && [ -w "${_cfg}" ] || return 0
    _tmp=$(mktemp) || return 0
    fix_config_render "${_cfg}" "${_tmp}" || { rm -f "${_tmp}" >/dev/null 2>&1 || true; return 0; }
    if cmp -s "${_cfg}" "${_tmp}"; then
        rm -f "${_tmp}" >/dev/null 2>&1 || true
        return 0
    fi
    cp -f "${_cfg}" "${_cfg}.fix-config.bak" || { rm -f "${_tmp}" >/dev/null 2>&1 || true; return 0; }
    chmod 600 "${_cfg}.fix-config.bak" 2>/dev/null || true
    mv "${_tmp}" "${_cfg}" || return 0
    chmod 600 "${_cfg}" 2>/dev/null || true
}

# {{APP_NAME}} fix-config
# {{APP_NAME}} fix-config --input-file "{{HOME}}/.ssh/config"
# {{APP_NAME}} fix-config --output-file "{{HOME}}/ssh-config.commented"
# {{APP_NAME}} fix-config --input-file "{{HOME}}/.ssh/config" --output-file "{{HOME}}/ssh-config.commented"
```

## 5. How to specialize

1. Put the OS table and the add / update / review moments in the product domain requirement.  
2. Dual-mention the typed verb on the CLI-interface requirement.  
3. Translate the help sentence in the product language requirement. Keep the command token Latin.  
4. Run the automatic pass once per process, before dispatch, with no message.  
5. Proof: comment vs delete, each OS class, flag matrix, automatic pass on a version line, one JSON object.

## 6. Design-time verification

| Gate | Intent |
|------|--------|
| Alpine comments `GSSAPI*` | Active prefix gone; the word remains in a comment; other keys stay |
| Termux comments the three algorithm keywords | `GSSAPI*` stays active on that class |
| posix | Neither family is commented |
| Flags | Neither, input only, output only, both |
| Automatic pass | Version line comments `{{HOME}}/.ssh/config` and prints no comment banner |
| Idempotent | Second pass does not rewrite |

## 7. Protection Rule (Sacred)

Future agents **MUST NOT**:

1. Delete an unsupported keyword instead of commenting it.  
2. Comment `GSSAPI*` on an OS that accepts GSSAPI, or comment the algorithm keywords on an OS that accepts them.  
3. Skip the automatic pass, or print from it.  
4. Create `{{HOME}}/.ssh/config` when the automatic pass finds it missing.  
5. Number the verb on a TTY menu.  
6. Strip this sample “for brevity.”  
7. Treat this mold as product-source authority.

**Last Updated**: 2026-09-30  
**Owner**: {{OWNER}}  
**Version history:**  
- **1.0.0** (2026-09-30): Portable comment-in-place for unsupported OpenSSH client keywords. Sample render and automatic pass.
