# copier-f0

[![ci](https://github.com/petr-korobeinikov/copier-f0/actions/workflows/ci.yml/badge.svg)](https://github.com/petr-korobeinikov/copier-f0/actions/workflows/ci.yml)
[![release](https://img.shields.io/github/v/release/petr-korobeinikov/copier-f0)](https://github.com/petr-korobeinikov/copier-f0/releases/latest)
[![license](https://img.shields.io/github/license/petr-korobeinikov/copier-f0)](LICENSE)

A [Copier](https://copier.readthedocs.io/) template for a Flipper Zero app.
The project you get has ufbt with a pinned SDK, host tests, CLion,
OpenSpec, git-flow, prek hooks, CI, a docs site and a release task.

You need macOS and [mise](https://mise.jdx.dev/).
mise installs the rest, Copier included.

> [!IMPORTANT]
> For most vibe-coded apps of a single file, this template is overkill.
> Its rules are strict:
> every change is planned as an OpenSpec change before its code is written,
> a session either plans or implements,
> and nothing is committed before its diff is reviewed.
> It does not suit vibe coding with one-shot prompts.

## Create a project

Clone this repository: Copier is pinned in it.

```shell
git clone https://github.com/petr-korobeinikov/copier-f0.git
cd copier-f0
mise trust
mise install
```

Generate the project:

```shell
mise exec -- copier copy gh:petr-korobeinikov/copier-f0 ../f0-my-app
```

Copier asks about the app and its license.
If you pick Other as the license, add your own `LICENSE` file.

Set the project up and make the first commit:

```shell
cd ../f0-my-app
git init
mise trust
mise install
mise run setup
git add -A
git commit -m "chore: generate from copier-f0"
```

The commit lands on `develop`.

## Update a project

Commit everything in the project.
Then, in the `copier-f0` clone:

```shell
git pull
mise install
GIT_CONFIG_COUNT=1 \
    GIT_CONFIG_KEY_0=status.showUntrackedFiles \
    GIT_CONFIG_VALUE_0=normal \
    mise exec -- copier update --skip-answered "$(cd ../f0-my-app && pwd -P)"
```

Copier asks only the new questions.
If it reports a conflict, find the `<<<<<<<` markers in the files and fix them by hand:
the hooks won't commit them.

Check the project and commit:

```shell
cd ../f0-my-app
mise install
mise run check-workflow
git add -A
git commit -m "chore: update from copier-f0"
```

`mise run check-workflow` runs the project's CI locally.

<details>
<summary>Why the update command is so long</summary>

- Copier takes the new template from GitHub;
  the clone only gives it Copier's pinned version.
- Copier fails on a path with `..`, so the path is made absolute.
- Where git's `status.showUntrackedFiles` is `all`,
  the SDK's files overflow Copier's call to git;
  the `GIT_CONFIG_*` variables turn it back to `normal`.

</details>
