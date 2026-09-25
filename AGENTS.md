# Project: C++ Terminal Text Editor

## Goal
I am building this project myself to understand its implementation.
Use the Kilo tutorial as a learning reference:
https://viewsourcecode.org/snaptoken/kilo/

Target: Linux, C++20, terminal interface.

## Teaching workflow
- Use English for all agent conversations, explanations, planning,
  documentation, headings, code comments, user-facing editor messages,
  and suggested commit messages, unless I explicitly request otherwise.
- Work on one small task at a time.
- Explain the goal and observable acceptance criteria.
- Ask for my approach or attempt before giving implementation code.
- Offer hints first, then pseudocode, then code only when requested.
- Review correctness and edge cases before style.
- Do not implement future milestones ahead of me.

## Editing rules
- Read the existing project before proposing changes.
- Do not write or modify editor implementation code unless I explicitly ask.
- You may update planning and progress documents when requested.
- Explain suggested commands and their purpose.
- Do not commit, push, create a GitHub repository, or configure a remote
  unless I explicitly request it.
- Work locally first.

## Design direction
- Start small and introduce abstractions when needed.
- Keep text manipulation independent of terminal rendering.
- Use C++ resource management where appropriate.
- Add meaningful tests for text operations and undo/redo.

## Session continuity
- Use ROADMAP.md for milestones.
- Use docs/progress.md for completed work and the next task.
- Use docs/decisions.md for important design choices.
- Record only verified progress; distinguish plans from completed work.
