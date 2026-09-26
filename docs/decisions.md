# Decision Log

## Confirmed requirements from your instructions

These are explicit project requirements, not implementation choices assumed to have your approval.

| Topic | Confirmed requirement | Source |
| --- | --- | --- |
| Platform | Linux, C++20, terminal interface | `AGENTS.md` |
| Working language | English for all agent conversations, explanations, planning, documentation, headings, code comments, user-facing editor messages, and suggested commit messages, unless you explicitly request otherwise | Language-policy request and updated `AGENTS.md` |
| Arabic support | Arabic is a confirmed product requirement, independent of the working language. Plan UTF-8 preservation, Unicode editing/history, and shaping/bidirectional investigation separately. UTF-8 file support alone is not complete Arabic editing support | Language-policy and Arabic-support request |
| Feasibility before design | Investigate Arabic shaping/bidirectional feasibility in 2.5 before committing to text-coordinate and rendering designs; keep full implementation in 10.6 and final validation in 11.6 | Documentation-correction request |
| Temporary learning scope | An initial ASCII-only milestone is acceptable only as a temporary limitation; Arabic support stays on the roadmap | Arabic-support request |
| Learning | You build the project yourself, one small task at a time. Your attempt comes before implementation code; hints precede pseudocode, and code is provided only when requested | `AGENTS.md` |
| Reference | Use Kilo as a learning reference | `AGENTS.md` |
| Design | Separate text operations from rendering; start small and introduce abstractions when needed | `AGENTS.md` |
| Resources | Use C++ resource management where appropriate | `AGENTS.md` |
| Tests | Meaningful text-operation and undo/redo tests, with validation throughout the milestones | `AGENTS.md` and planning request |
| Work sequence | Follow Kilo’s numbered concept steps, one per session unless requested otherwise; ROADMAP.md tracks broader scope and required prerequisites | Tutorial-alignment request, 2026-09-26 |
| Local-first workflow | Work locally; no commits, pushes, GitHub repository creation, or remote configuration without an explicit request | `AGENTS.md` |

## Proposed choices — not yet agreed

Discuss these when the relevant task is reached. None is an approved implementation decision or completed work. Arabic support itself is confirmed; the mechanisms below are still open.

| Topic | Initial proposal or open choice | When and why to discuss it |
| --- | --- | --- |
| Screen drawing | Introduce escape sequences when reached in Kilo; terminal settings already use a local C++ guard | Milestone 3, after the required Arabic feasibility investigation |
| Text representation | Evaluate `std::vector<std::string>` as an initial representation | Milestone 4: simple line storage, with editing costs and UTF-8 preservation considered explicitly |
| UTF-8 storage and malformed input | Preserve valid UTF-8 without implicit normalization; decide how malformed file bytes and incomplete/invalid input sequences are handled | Tasks 4.1, 4.6, and 6.6: distinguish preserving file content from decoding input safely |
| Unicode coordinates | Define separate byte offsets, code-point positions, grapheme boundaries, and terminal display columns; choose their representation and conversions | Task 4.6, informed by 2.5 before approval: these units are not interchangeable |
| Movement and deletion units | Evaluate grapheme-cluster movement/deletion versus a documented code-point learning step. Decide combining-mark behavior, insertion boundaries, and how cursor positions remain valid | Tasks 4.6 and 6.6: Arabic diacritics require explicit editing semantics; any simplified step must remain labeled temporary |
| Terminal columns | Choose a display-width strategy, dependency policy, and behavior for tabs, combining marks, wide characters, and terminal disagreements | Initial constraints in 2.5 before rendering design; decisions in 4.6 and implementation in 6.6: logical text offsets do not directly specify screen columns |
| Line endings | Decide support for `LF` and `CRLF` and preservation of a final newline's presence or absence | Milestone 4, before loading files: avoid unintended changes on load/save |
| Tests | Choose the simplest suitable way to run tests without a TTY | Milestone 4: avoid adding a framework without a need |
| Saving | Evaluate writing to a temporary file before replacement, including its guarantees and limits | Milestone 6: reduce the risk of damaging an existing file on write failure |
| Search | Start by evaluating literal matching; decide case sensitivity, wraparound, normalization, and diacritic handling | Milestone 7: make results and Unicode match boundaries predictable |
| Highlighting | One language and a limited rule set, without a full parser | Milestone 8: keep the scope understandable and testable |
| Auto-indent | Evaluate copying the current line's leading whitespace | Milestone 9: decide tab behavior and the effect of the split position |
| Undo/Redo | Compare inverse-operation history with snapshots before choosing; define Unicode-safe grouping and exact text/cursor restoration | Milestone 10: decide memory use, grouping, and the relationship between history and saved state |
| Arabic shaping and bidi | Investigate editor-managed versus terminal-provided presentation, possible library needs, and logical versus visual movement. Do not assume consistent terminal support | Initial feasibility in 2.5 before coordinate/rendering decisions; full implementation/integration in 10.6 and final validation in 11.6. Include Arabic/English mixtures, punctuation, digits, and diacritics, then integrated deletion and scrolling tests |

## Arabic support investigation record — pending

No terminal compatibility results or shaping/bidi implementation decisions have been verified. Task 2.5 will start this record before coordinate/rendering designs are approved, documenting feasibility observations, constraints, options, and unresolved risks. Task 10.6 will extend it with full implementation and integration results. Record the following as evidence becomes available, distinguishing early terminal experiments from later editor tests:

- The terminal, version, font, locale, and relevant settings used for each experiment.
- Fixtures covering Arabic, mixed Arabic/English lines, punctuation, digits, and diacritics.
- Expected and observed shaping, ordering, cursor placement, movement, deletion, and scrolling behavior.
- Which behavior the editor provides, which depends on the terminal/font/environment, and how unsupported environments are handled.
- The agreed support scope, required implementation follow-ups, known limitations, and separate automated-model and manual-terminal results.

Task 11.6 will validate the resulting support statement. File preservation, Unicode editing/history, and Arabic presentation must each have their own evidence; success in one category does not establish the others.

## Adopting a decision

Once we agree on a choice, move it to the approved implementation decisions section with the date, rationale, main alternatives, and testing implications. Record subsequent changes and their reasons. A proposal does not become an approved decision simply because it appears in the roadmap.

## Approved implementation decisions

- **Build tool — GNU Make:** explicitly chosen by the user for task 1.2. Start with one program target to automate the successful direct `g++` build. `CMake` was an earlier alternative; no comparative evaluation was performed. Verify initial build, no-op rebuild, and rebuild after a source change. The choice is confirmed; the user-written one-target Makefile and supplied build/rebuild evidence were reviewed and accepted for task 1.2. Build-directory organization and ignore rules were subsequently verified in tasks 1.3–1.4.

- **Terminal restoration — local C++ guard:** implemented at the user's request
  and retained in the 2026-09-26 review. Save the complete original settings;
  explicitly restore to report failures through exit status, with destructor
  fallback for early returns. This adapts Kilo's global snapshot/atexit pattern.
  VMIN=1 and VTIME=0 retain blocking reads; TCSANOW retains immediate changes
  without discarding queued input. Signal termination remains outside supported
  cleanup paths. No generic resource framework or signal handlers are planned
  for the current step.
