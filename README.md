# Git Try 2025

This is an attempt to write a simple git clone in C with some basic functionality.

## Commands

- git init [<directory>]
  - Creates an empty Git repository - it should create the passed directory, a **.git** subdirectory, and other subdirectories in order for the program to recognize that it is inside a git repository and for it to work.
- git status
  - Displays the current status of the repository - it should display the current branch name, the currently modified files and the currently untracked files that are not ignored as described by a **.gitignore** file.
- git add [<pathspec>...]
  - Add contents of new or changed files to the index. The "index" (also known as the "staging area") is what you use to prepare the contents of the next commit.
- git restore [--staged] [<pathspec>...]
  - Restore specified paths in the working tree with some contents from the current branch. if `--staged` option is passed, it should restore from the "staging area"
- git commit [-m <msg>]
  - Creates a new commit containing the current contents in the "staging area"
- git log
  - List commits that are reachable by following the parent links from the given commit(s), but exclude commits that are reachable from the one(s) given with a ^ in front of them. The output is given in reverse chronological order by default.
- git revert
  - Given one or more existing commits, revert the changes that the related patches introduce, and record some new commits that record those reverted changes.

### Extra Optional Commands

- git branch <branch-name>
  - Creates a new branch based on the content of the current branch

### Challenge

- git merge
- git rebase

The commands with `<pathspec>` should allow the user to pass `.` as an indication to add or remove everything (recursively)

## Desgin

### What is a commit

### What is a branch

### How is a commit stored

### How is a branch stored
