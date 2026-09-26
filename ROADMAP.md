# Terminal Text Editor Roadmap

The goal is to build and understand the project yourself on Linux using C++20. Checked items are complete; unchecked items remain pending or partial. We will work on one small task at a time: explain the goal and acceptance criteria, review your attempt, and check correctness and edge cases before style.

English is the project's working language for conversations, explanations, planning, documentation, headings, code comments, user-facing editor messages, and suggested commit messages, unless you explicitly request otherwise. Arabic support is a separate, confirmed product requirement.

Learning reference: [Kilo tutorial](https://viewsourcecode.org/snaptoken/kilo/). The tutorial uses C; we will learn from its sequence of ideas and discuss C++ choices as needed. Open choices are recorded in [decisions](docs/decisions.md), and the current state is recorded in [progress](docs/progress.md).

## Learning sequence

Use Kilo's numbered steps for concept order and one small step per session;
these eleven milestones track product scope and acceptance, not session order.
Current point: chapter 2, step 7 (noncanonical input). Next: step 8 (display
keypresses). Chapters 1–2 and their step diffs were read on 2026-09-26; read
later chapters when reached. Explain C++ adaptations and necessary departures
before making them. Do not implement later text-model, Unicode, or feature work
just because it appears here. The early Arabic feasibility prerequisite below
is a deliberate project requirement beyond Kilo and remains in force.

## Arabic support: staged requirement

An initial ASCII-only learning milestone is acceptable as a temporary limitation. It does not remove Arabic support from the roadmap. UTF-8 file preservation alone is not complete Arabic editing support.

1. **Preserve UTF-8 content:** define storage and file policies in 4.1, load UTF-8 in 5.1, and verify lossless load/save round trips in 6.5. Test Arabic and mixed Arabic/English content, punctuation, digits, and diacritics. Do not silently normalize or replace valid content.
2. **Make editing Unicode-aware:** define byte offsets, code points, grapheme clusters, and terminal display columns in 4.6. Implement and test input, cursor movement, deletion, and display mapping in 6.6, then Unicode-aware undo/redo in 10.5. Decide explicitly which unit each operation uses; do not treat a byte, code point, grapheme cluster, and display column as interchangeable.
3. **Investigate Arabic presentation early, implement later:** conduct initial shaping and bidirectional feasibility work in 2.5 before committing to text-coordinate or rendering designs in milestones 3–4. Use the findings to inform 4.1 and 4.6. Keep full implementation and integration in 10.6 after the Unicode editing foundation, and final validation/documentation in 11.6. Include mixed Arabic/English lines, punctuation, digits, diacritics, selection-free cursor navigation, and horizontal scrolling. Record what the editor handles and what depends on the terminal, font, and environment. Agree on the supported scope after investigation rather than claiming full support from successful UTF-8 round trips.

These stages span the milestones below; their completion must be verified separately. All three are pending.

## 1. Build setup

- [x] 1.1 Check for a compiler supporting C++20, then build and run a small experimental program with a direct compiler command.
- [x] 1.2 Choose and record a build tool, then add one program target.
- [x] 1.3 Enable appropriate warnings, choose a build output directory, and exclude generated output from version control.
- [x] 1.4 Document the build and run commands, and try building in a fresh output directory.

Tests: the experimental program builds using C++20 and exits with status 0. After configuring the build tool, reproduce that result with a clean build and no warnings.

Completion criteria: documented, repeatable build and run steps that do not depend on old build artifacts.

## 2. Terminal control

- [x] 2.1 Read the current terminal settings and understand `termios`, canonical mode, and echo.
- [ ] 2.2 Enable raw mode incrementally and observe each change.
- [x] 2.3 Save and restore the original settings using appropriate C++ resource management.
- [x] 2.4 Handle setup failures and non-TTY execution, and define supported exit paths.
- [ ] 2.5 Conduct an initial Arabic shaping/bidirectional feasibility investigation before committing to text-coordinate or rendering designs. Examine mixed Arabic/English lines, punctuation, digits, and diacritics in the intended terminal environments. Record observations, likely editor versus terminal responsibilities, logical/visual position constraints, possible library needs, open risks, and implications for milestones 3–4. This is an investigation, not full editor implementation; integration remains in 10.6.

Review against current code and recorded evidence (2026-09-26):

| Task | Status | Evidence or remaining work |
| --- | --- | --- |
| 2.1 | Complete | Current settings were read and flag checks reviewed; the user's cat and editor observations distinguish canonical input from echo. |
| 2.2 | Partial | ECHO/ICANON changes and immediate invisible q are verified. Other raw-mode flags and their observations remain pending; VMIN=1/VTIME=0 is blocking input, not the later timeout experiment. |
| 2.3 | Complete | The user-approved explicit C++ cleanup path saves the full snapshot and restores it on q, injected EOF, read error, and injected setup failure. Pseudo-terminal comparisons verified exact restoration, including nondefault VMIN/VTIME. A scope guard is not required by this task; all normal paths after a change attempt must reach cleanup. |
| 2.4 | Complete | Injected setup/read failures and non-TTY input produce diagnostics and status 1. Injected restoration failure is reported with status 1. Supported cleanup paths and signal/crash/exception limitations are documented; completion does not promise restoration when the restoration syscall itself fails. |
| 2.5 | Pending | No Arabic shaping/bidirectional feasibility investigation or terminal/font matrix has been performed. |

The user also manually verified the explicit-cleanup build: q without Enter
exited immediately, shell typing returned to normal, and exit status was 0.
This verifies observable behavior; exact attribute restoration comes from the
separate pseudo-terminal evidence. Milestone 2 overall remains incomplete.
Next learning step: **Kilo chapter 2, step 8 — Display keypresses**, not implemented.

Tests: manually read a key in a TTY without Enter or echo. Compare terminal settings before execution and after normal exit and a controlled error. Non-TTY input must produce a clear message. Restoration after `SIGKILL` cannot be guaranteed. For 2.5, use reproducible terminal experiments and record terminal/font/settings, expected versus observed shaping and ordering, cursor positioning behavior, and unresolved questions; do not report untested editor behavior as verified.

Completion criteria: the intended behavior is observable, and terminal settings are restored on the supported, tested exit paths. The 2.5 feasibility findings and design implications are documented before coordinate/rendering choices are approved; Arabic implementation is still pending.

## 3. Input and screen drawing

Design prerequisite: review the findings from 2.5 before committing to rendering or cursor-positioning designs.

- [ ] 3.1 Read input and distinguish ordinary characters, `Escape`, and the exit key. An ASCII-only first exercise is temporary.
- [ ] 3.2 Decode arrow-key sequences and handle incomplete or unknown sequences.
- [ ] 3.3 Draw a simple screen using escape sequences and position the cursor.
- [ ] 3.4 Read the screen dimensions and handle resizing and small screens.

Tests: try arrow keys, standalone `Escape`, and incomplete sequences; input must not hang. Resize the terminal and check that drawing and cursor placement stay within the screen.

Completion criteria: a stable input/render loop, a known exit key, and defined behavior on small screens. This milestone does not establish Unicode or Arabic editing support.

## 4. Text model

Design prerequisite: use the findings from 2.5 when agreeing on coordinates in 4.1 and 4.6. Unresolved feasibility questions must remain explicit.

- [ ] 4.1 Agree on line storage, coordinates, UTF-8 preservation, and line-ending policies.
- [ ] 4.2 Create a text model independent of the terminal and define valid cursor positions.
- [ ] 4.3 Add insertion and deletion within a line.
- [ ] 4.4 Add line splitting and joining.
- [ ] 4.5 Add a way to run text-model tests without a TTY.
- [ ] 4.6 Record explicit decisions about byte offsets, code points, grapheme clusters, and terminal display columns, including operation boundaries and malformed UTF-8 handling. Distinguish logical text positions from visual positions. Any ASCII-only operations are temporary and must be extended in 6.6.

Tests: automate empty-document, line-boundary, empty-line, insertion, deletion, split, and join cases. Reject or handle invalid coordinates according to the agreed contract. Check text and expected cursor position after each operation. Add UTF-8 storage fixtures with Arabic and diacritics; distinguish preservation tests from editing tests.

Completion criteria: basic operations and their tests run without rendering or terminal setup; UTF-8 storage and coordinate contracts are documented, with temporary limitations identified.

## 5. File viewing and scrolling

- [ ] 5.1 Load files into the text model, preserving valid UTF-8 content, and report read errors clearly.
- [ ] 5.2 Draw the visible text, handling tabs and control characters safely.
- [ ] 5.3 Connect cursor movement to the text and add vertical, then horizontal, scrolling.
- [ ] 5.4 Add file information, cursor position, and empty-file states.

Tests: use empty and multiline fixtures, long lines, files with and without a final newline, and UTF-8 files containing Arabic, mixed text, digits, punctuation, and diacritics. Test the agreed loading policy. Try missing/unreadable files, document boundaries, and resizing while scrolling. Test viewport calculations if extracted into independent functions. Record any temporary display/navigation limitations for non-ASCII text; loading successfully is not proof of correct Arabic display.

Completion criteria: files load according to the agreed preservation policy, viewing works within the documented temporary scope, the cursor remains visible within that scope, and read errors do not break terminal cleanup. Unicode movement and Arabic presentation remain tracked in 6.6 and 10.6.

## 6. Editing and saving

- [ ] 6.1 Connect typing, `Enter`, `Backspace`, and `Delete` to tested text-model operations.
- [ ] 6.2 Track unsaved changes and add an appropriate exit warning.
- [ ] 6.3 Save named files, then prompt for a filename for new documents.
- [ ] 6.4 Handle save failures without clearing the modified state; choose the save strategy before implementation.
- [ ] 6.5 Verify lossless UTF-8 load/save round trips, including Arabic and mixed text, without implicit normalization or replacement. Test line-ending handling separately under the agreed policy.
- [ ] 6.6 Extend input, cursor movement, insertion, deletion, splitting, joining, and scrolling to follow the Unicode contracts from 4.6. Handle UTF-8 input arriving in partial sequences, apply the agreed malformed-input policy, and map logical positions to terminal display columns under the documented rendering scope.

Tests: automate editing sequences at line boundaries and load/save/reload tests using temporary files. Check line endings under the selected policy. Test cancellation of the filename prompt and failed writes: failure must retain the modified state and protect the original file under the agreed save guarantees. Check byte-for-byte preservation for unchanged valid UTF-8 fixtures when line endings are unchanged. Test multibyte characters, combining diacritics, mixed text, partial input sequences, and deletion/movement boundaries using the chosen code-point or grapheme-cluster policy. No edit may accidentally split a UTF-8 sequence.

Completion criteria: opening, editing, saving, and reopening preserves expected content; failures are clear, and exit does not silently discard changes. UTF-8 preservation and Unicode editing pass distinct tests. Arabic shaping and bidirectional presentation are still pending until 10.6 and 11.6.

## 7. Search

- [ ] 7.1 Define matching, case sensitivity, and wraparound policies, including whether normalization or diacritic-insensitive matching is supported.
- [ ] 7.2 Search the text model and return match positions using the agreed coordinate contract.
- [ ] 7.3 Add query input, navigation between results, and highlighting of the current result.
- [ ] 7.4 Support cancellation and restore the previous cursor and viewport positions.

Tests: automate empty queries, no matches, repeated matches, and matches at document boundaries under the chosen policy. Include Arabic queries, diacritics, and mixed text; matches and cursor placement must respect the agreed Unicode boundaries. Manually test search and cancellation after scrolling.

Completion criteria: results are predictable and tested, and searching or cancelling does not modify the text. Any normalization or diacritic matching limitations are explicit.

## 8. Syntax highlighting

- [ ] 8.1 Choose one language and a limited initial set of highlighting rules.
- [ ] 8.2 Separate calculation of highlighted spans from rendering escape sequences.
- [ ] 8.3 Highlight keywords, comments, and strings according to the selected rules.
- [ ] 8.4 Update highlighting after edits, including multiline comment state if supported.

Tests: automate similar-looking keywords, comment markers inside strings, incomplete strings, and multiline state if supported. Include Arabic content in strings/comments so spans do not split UTF-8 sequences. Test highlighting with search results and scrolling.

Completion criteria: selected rules are documented and tested; highlighting updates without changing text or corrupting cursor placement.

## 9. Line numbers, Go to line, and Auto-indent

- [ ] 9.1 Add a line-number gutter and update its width as the line count changes.
- [ ] 9.2 Add `Go to line`, converting user-visible line numbers to model coordinates.
- [ ] 9.3 Define an `Auto-indent` policy and apply it when splitting a line.

Tests: move from 9 to 10 lines and 99 to 100 on a narrow screen. Test valid line numbers, zero, negative and out-of-range values, nonnumeric input, and cancellation. Automate indentation cases for empty lines and lines beginning with spaces or tabs under the selected policy. Include lines containing Arabic and diacritics to verify that indentation preserves their content.

Completion criteria: the gutter does not break rendering or scrolling, navigation handles invalid input, and indentation produces tested, expected text.

## 10. Undo/Redo

- [ ] 10.1 Agree on undo units, typing-group boundaries, and a memory policy.
- [ ] 10.2 Record edits and implement their inverses independently of the terminal.
- [ ] 10.3 Add `Redo` and invalidate the old redo branch after a new edit following undo.
- [ ] 10.4 Restore cursor positions and track the saved state through undo and redo.
- [ ] 10.5 Make history and grouping respect the Unicode editing contract, preserving exact text and valid cursor boundaries for Arabic, combining marks, and mixed text.
- [ ] 10.6 Build on the initial feasibility findings from 2.5, resolve remaining Arabic shaping/bidirectional questions, and implement and integrate the agreed presentation support. Test mixed Arabic/English lines, punctuation, digits, diacritics, cursor movement, deletion, and scrolling. Record logical versus visual movement choices, the editor/terminal responsibility boundary, tested terminals/fonts/settings, and required follow-up work. Address agreed support gaps before claiming Arabic presentation support.

Tests: automate insertion, deletion, splitting, joining, and `Auto-indent`. Undoing a complete sequence must restore text and cursor; redoing it must restore the edited state. Test empty history, editing after undo, returning to a saved state, saving mid-history, and history limits. Repeat with Arabic, diacritics, and mixed text, checking exact content and Unicode boundaries. For shaping and bidi, keep a reproducible manual terminal test matrix and record observed behavior and limitations separately from automated model results.

Completion criteria: text, cursor, and modified state remain correct across tested sequences; Unicode text operations and history are testable without a TTY. The Arabic presentation implementation builds on 2.5 with documented integration results, explicit responsibility boundaries, and an agreed supported scope; required follow-up work is completed or explicitly recorded as a remaining requirement, never implied complete.

## 11. Final validation and documentation

- [ ] 11.1 Run the accumulated tests from a clean build and fix failures.
- [ ] 11.2 Exercise a full session: open, edit, search, navigate, undo, redo, save, and reopen.
- [ ] 11.3 Review errors, moderately large files, small screens, and terminal restoration.
- [ ] 11.4 Run memory and undefined-behavior checking tools if available and document results.
- [ ] 11.5 Write build instructions, usage instructions, shortcuts, known limitations, and final decisions.
- [ ] 11.6 Validate and document Arabic support in three separate categories: UTF-8 preservation, Unicode editing/history, and shaping/bidirectional presentation. Repeat the mixed-text terminal matrix and distinguish editor guarantees from terminal/font/environment dependencies.

Tests: run all accumulated tests and a complete manual scenario; compare saved content against expectations. Include Arabic/English text, punctuation, digits, and diacritics throughout the scenario. Record what actually ran and any remaining limitations.

Completion criteria: build and usage instructions are repeatable, agreed checks pass, and limitations are documented. Arabic support claims match verified behavior in each category; unresolved required support prevents claiming the product requirement complete. This phase consolidates earlier validation rather than introducing testing for the first time.
