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
- Work on one small Kilo-sized step per session unless I ask otherwise.
- Identify the Kilo chapter, numbered step, and link before each task.
  Read its explanation and step diff before proposing a change. Chapters 1
  and 2 were read during the 2026-09-26 review; read later chapters when reached.
- Follow Kilo's order of concepts and size of changes, not just its feature list.
  Explain the idea, change a few relevant lines, build, run, observe, then stop.
- State deliberate C++ adaptations and other departures from Kilo and why each
  is needed now. Keep Linux and C++20; do not copy C wholesale or convert to C.
- Explain the goal and observable acceptance criteria.
- Ask for my approach or attempt before giving implementation code.
- Offer hints first, then pseudocode, then code only when requested.
- Review correctness and edge cases before style.
- Do not implement future milestones ahead of me.
- When I explicitly request implementation, carry out that small step and
  explain the diff and verification; do not ask again for permission to code.
- Prefer code I can explain line by line. Do not add abstractions or tests for
  polish, introduce artificial mistakes, or rush work/commits for GitHub activity.

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
- Preserve staged Arabic support in ROADMAP.md: UTF-8 preservation, Unicode-aware
  editing/history, and shaping/bidirectional presentation are separate requirements.
  Keep the early presentation feasibility investigation before coordinate/rendering
  design; identify it as a deliberate departure from Kilo, not completed support.

## Session continuity
- Use ROADMAP.md for milestones.
- Use docs/progress.md for completed work and the next task.
- Use docs/decisions.md for important design choices.
- Record only verified progress; distinguish plans from completed work.
- Keep docs/progress.md concise: current chapter/step, change, evidence, result,
  and one next small step. Distinguish user observations from agent-run checks.
- Treat ROADMAP.md as long-term scope and acceptance criteria, not a replacement
  for Kilo's teaching sequence. Discuss required departures before taking them.
