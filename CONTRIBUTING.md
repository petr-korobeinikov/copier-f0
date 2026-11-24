# Contributing

This repository is the template itself:
`copier.yml` asks the questions,
and everything under `template/` becomes the generated project.
It has one branch, `main`, and no hooks or git-flow of its own;
the projects it generates have both.

## Check a Change

A change is checked by use, in a project generated from the working tree,
where Copier takes uncommitted changes too:

```shell
mise trust
mise install
mise exec -- copier copy . "$(mktemp -d)/f0-check"
```

Bring the project to life as [Create a project](README.md#create-a-project) says,
then exercise what the change touches:
the build, the tests, the hooks, the docs site,
and CI through `mise run check-workflow`.
A change to how a project updates is checked
by `copier update` on a project generated before it.

A tool's version in `template/mise.toml` changes together with `template/mise.lock`,
written by `mise lock` in a generated project and carried back.

## CI

`.github/workflows/ci.yml` runs on every push to `main` and on every pull request.
Its jobs are the generated project's `ci.yml`, job by job and step by step,
each run in a project that `.github/actions/generate` generates from the commit under test,
so a change to the project's `ci.yml` is carried into this one.
`mise run check-workflow`, run in this repository, puts the jobs through act on the Mac;
Copier takes uncommitted changes there too.

## Commits

A commit message is a [Conventional Commit](https://www.conventionalcommits.org/), in English:
the subject alone, in the imperative mood,
lowercase after the prefix, without a closing period,
72 characters at most.
No line of it credits an AI agent or a model.
Commits are signed, and the history of `main` stays linear.
