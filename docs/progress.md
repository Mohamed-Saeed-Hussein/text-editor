# Current Progress

## Current point

[Kilo chapter 2, step 7 — Turn off canonical mode](https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html#turn-off-canonical-mode).
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
crashes, and SIGKILL still bypass cleanup; README explains recovery. No step 8,
commit, or push.

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

## Next small step — Chapter 2, step 8: Display keypresses

Explain displaying each received byte's numeric value and a printable ASCII
character, then ask for the user's approach before implementation unless they
explicitly request agent implementation. Use an unsigned-char conversion when
classifying bytes in C++; do not print control bytes literally. Keep q exit
and restoration. Build, run, and observe ordinary keys and control keys; do not
combine this with step 9's signal changes. This step is not implemented or tested.
