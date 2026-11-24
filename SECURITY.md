# Security Policy

## Supported Versions

Only the latest release of the template receives security fixes.
A generated project takes a fix by `copier update`,
as [Update a project](README.md#update-a-project) says.

## Reporting a Vulnerability

Please report security vulnerabilities privately
through GitHub's [private vulnerability reporting][report].
Do not open a public issue for security problems.
This covers the template and what it puts into a generated project:
its toolchain setup, hooks, CI and release.

You can expect an initial response within a few days.
This is a personal project,
so fixes are best-effort.

[report]: https://github.com/petr-korobeinikov/copier-f0/security/advisories/new

## What Generating Runs

The template uses none of the features Copier calls unsafe —
Jinja extensions, tasks and migrations —
so `copier copy` and `copier update` run no command of the template's
and never need `--trust`.
Its code runs only when called in the generated project:
`mise install` installs the tools pinned in the project's `mise.lock`,
and `mise run setup` deploys the Flipper SDK under `sandbox-exec`.
The generated project's own policy is its `SECURITY.md`.

## Dependency Security Posture

Copier is this repository's only tool.
It is pinned in `mise.toml`
and installs from the dependency graph committed in `.mise/locks/`,
every package pinned by its hash,
into a venv of its own on a private Python.
A bump is audited and lands as a change of its own.
