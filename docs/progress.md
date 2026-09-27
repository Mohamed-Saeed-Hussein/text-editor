# Current Progress

## Current point

[Kilo chapter 2, step 8 — Display keypresses](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html#display-keypresses).
Verified by agent checks and the user’s manual observation.
Chapter 1's build setup and chapter 2's input, q, echo, restoration, and ICANON
increments are complete with the C++ adaptations below. This is not full raw
mode. ROADMAP.md 1.1–1.4, 2.1, 2.3, and 2.4 are complete for the documented
supported paths. Task 2.2 is partial; task 2.5 is pending. Milestone 2 is incomplete.
Arabic preservation, Unicode editing/history, and shaping/bidi work remain pending.

## Evidence retained from earlier steps

- User build transcripts verified C++20 compilation, warnings enabled, clean
  output-directory rebuilding, no-op Make builds, and exit status 0.
- User's cat observation distinguished echo and canonical line editing from
  the completed line delivered to the program.
- User manually verified both echo-only (q required Enter) and noncanonical
  input (q exited immediately), invisible typing, restored shell echo, and status 0.
- Earlier agent pseudo-terminal checks verified exact attribute restoration on
  q, EOF in the canonical experiment, and forced read errors. SIGINT bypassed
  cleanup; stty sane restored echo. EOF is not claimed as a Ctrl-D gesture in
  the current noncanonical mode.

## 2026-09-26 — Explicit cleanup at step 7

Change: at the user's choice, replaced the restoration guard with the proposed
restoreTerminal helper and one cleanup block. After a settings-change attempt,
every normal return path must reach that block. Setup/read failures set status 1;
q and EOF leave the loop; restoration runs before the final return. EINTR during
restoration is retried. Other restoration errors are reported once with status 1.
This supersedes the earlier scope-guard choice recorded in the decision log.

Evidence: make rebuilt without warnings. Agent pseudo-terminal checks verified
immediate invisible q and status 0, from both canonical and already noncanonical
settings, and exact restoration including nondefault VMIN=7/VTIME=3. A forced
nonblocking read error returned 1 with a diagnostic and exact restoration.
Temporary /tmp LD_PRELOAD fault injection simulated a setup failure after
applying changed attributes: status 1, no input loop, exact restoration. Injected
EOF returned 0 and restored exactly. Injected restoration failure reported an
error and returned 1 (restoration necessarily failed; the harness recovered the
test terminal). /dev/null input returned 1 with a settings diagnostic. No test
hooks or framework were added to the project. The user subsequently manually
verified this explicit-cleanup build: q exited without Enter, shell typing
returned to normal, and echo $? reported 0.

Result: supported step-7 behavior retained with explicit control flow. There is
no destructor fallback for future early returns or exception unwinding. Signals,
crashes, and SIGKILL still bypass cleanup; README explains recovery. No commit
or push was made in that session.

Tutorial alignment remains: chapters 1–2 and their diffs (steps 1–19) were read;
later chapters remain unread. C++20, explicit checked cleanup, VMIN=1/VTIME=0,
TCSANOW, and initial status lines are deliberate adaptations. Full raw mode and
Kilo's timeout experiment are not implemented. The staged Arabic roadmap is unchanged.

## Roadmap evidence review

Reviewed the current source, README, and recorded verification; no tests were
rerun for this documentation-only review. Marked 2.3 and 2.4 complete based on
exact restoration and failure-path checks above, with explicit cleanup accepted
as the current C++ implementation. Kept 2.2 partial: disabling ECHO/ICANON does
not complete raw mode. Kept 2.5 pending: Arabic feasibility has not been studied.
Task 2.1 remains complete. No later milestones were marked complete.

## 2026-09-27 — Step 8 verified

Change: after a successful read, q still exits before display. Other bytes print
as decimal numbers, with the character appended only when std::isprint accepts
it. C++ adaptations: unsigned-char conversion makes classification safe and
numeric values nonnegative; std::cout formats the output and explicitly flushes
each line. Using isprint rather than Kilo's iscntrl also avoids emitting
nonprintable high bytes. Cleanup, error handling, and terminal flags are unchanged.
The step-8 explanation and displayed step diff were read before editing.

Agent evidence: make compiled with C++20, -Wall -Wextra -Wpedantic and no warnings.
A temporary Python pseudo-terminal harness checked exact immediate output for
a (97), Z (90), space (32), Ctrl-A (1), Tab (9), Enter/CR input (10), Escape (27),
DEL (127), NUL (0), and byte 255. Only printable bytes included characters.
Injected Up-arrow bytes produced separate 27, 91 ('['), 65 ('A') lines.
q produced no output, exited without Enter with status 0, and restored the full
original termios snapshot exactly. Local flags differed only by ECHO/ICANON;
signal behavior was not changed or exercised. Non-TTY /dev/null input returned
1 with the settings diagnostic. Earlier injected failure-path checks above were
not rerun. No persistent test harness was added.

User evidence: running ./build/text-editor and pressing a, Ctrl-A, Tab, Enter,
then Escape displayed 97 ('a'), 1, 9, 10, and 27. The user confirmed q exited
immediately and silently, shell typing was restored, and echo $? returned 0.

Result: step 8 is verified. Reviewed ROADMAP.md terminal-control criteria:
2.2 remains partial because the remaining raw-mode flags are not implemented;
2.3 and 2.4 retain their previously verified supported-path status. Task 2.5
remains pending, so milestone 2 is incomplete. Byte display does not establish
escape-sequence decoding or complete milestone 3. ROADMAP.md's older step-7/8
sequence text is historical; the current learning point is recorded here.
Step 9 is not implemented or started in this checkpoint.

## Next small step

In a future session, review Kilo chapter 2, step 9 — Turn off Ctrl-C and Ctrl-Z
signals — and ask for the user’s approach before implementation.
