# copier-f0

[![ci](https://github.com/petr-korobeinikov/copier-f0/actions/workflows/ci.yml/badge.svg)](https://github.com/petr-korobeinikov/copier-f0/actions/workflows/ci.yml)
[![release](https://img.shields.io/github/v/release/petr-korobeinikov/copier-f0)](https://github.com/petr-korobeinikov/copier-f0/releases/latest)
[![license](https://img.shields.io/github/license/petr-korobeinikov/copier-f0)](LICENSE)

A [Copier](https://copier.readthedocs.io/) template for a Flipper Zero app:
ufbt with the pinned SDK, host tests, CLion, OpenSpec, git-flow,
the prek hooks, CI, the docs site and the release.
The generated project's docs cover each of them.

It needs macOS, where `mise run setup` deploys the SDK under `sandbox-exec`,
and [mise](https://mise.jdx.dev/),
which installs everything else, Copier included.

> [!IMPORTANT]
> For most vibe-coded apps of a single file, this template is overkill.
> Its rules are strict:
> every change is planned as an OpenSpec change before its code is written,
> a session either plans or implements,
> and nothing is committed before its diff is reviewed.
> It does not suit vibe coding with one-shot prompts.

## Create a project

Copier is pinned in this repository's `mise.toml`,
so it runs from a clone of it,
and takes the template from GitHub:

```shell
git clone https://github.com/petr-korobeinikov/copier-f0.git
cd copier-f0
mise trust
mise install
mise exec -- copier copy gh:petr-korobeinikov/copier-f0 ../f0-my-app
```

Copier asks for the app's name, id, category, description, author and web page,
then for the docs site's address, the copyright year and the license:
MIT, GPL-3.0-only, Apache-2.0 or another by its SPDX id,
whose `LICENSE` the project adds itself.
Copier takes the template's latest release.

Then bring the project to life:

```shell
cd ../f0-my-app
git init
mise trust
mise install
mise run setup
git add -A
git commit -m "chore: generate from copier-f0"
```

`mise run setup` makes `main` and `develop` with git-flow,
installs the hooks and deploys the SDK;
the commit lands on `develop` through the hooks.

## Update a project

Commit everything in the project first,
then run the update from the root of the clone of this repository:

```shell
git pull
mise install
GIT_CONFIG_COUNT=1 \
    GIT_CONFIG_KEY_0=status.showUntrackedFiles \
    GIT_CONFIG_VALUE_0=normal \
    mise exec -- copier update --skip-answered "$(cd ../f0-my-app && pwd -P)"
```

Copier keeps the earlier answers and asks only the new questions.
A conflict stays in the file as git's markers.
Then check the project and commit:

```shell
cd ../f0-my-app
mise install
mise run check-workflow
git add -A
git commit -m "chore: update from copier-f0"
```

Why the command looks like this:
the project records the template as `gh:petr-korobeinikov/copier-f0`,
so Copier takes its new version from GitHub,
and the clone, pulled, only brings Copier's pin;
a path with `..` breaks Copier, so it is made absolute;
and the `GIT_CONFIG_*` variables stop the SDK's files from overflowing Copier's call to git
where `status.showUntrackedFiles` is `all`.
