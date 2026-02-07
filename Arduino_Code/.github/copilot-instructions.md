# Copilot / AI Agent Instructions — ROBOT_ARM_CONTROLE

Purpose
- Quickly orient AI coding agents to the single-sketch Arduino robot-arm project and its working patterns so contributions are safe and high-value.

Big picture
- This repository contains a single Arduino sketch: [arduino_code.ino](arduino_code.ino#L1). It runs on an Arduino-compatible board and controls 6 servos connected to pins {4,5,6,7,8,9}.
- The sketch exposes a very small serial command protocol (baud 9600) used by a GUI or serial monitor to: move individual servos, save poses, play stored programmes, and perform a smooth reset to home.

Key files & constants
- `arduino_code.ino` — the entire program. Key constants: `NUM_SERVOS = 6`, `MAX_STEPS = 50`, `STEP_DELAY = 15`, `HOME_POS = 90`.
- Servo pin mapping: `int pins[NUM_SERVOS] = { 4, 5, 6, 7, 8, 9 };`

Command protocol (observed exact behavior)
- Serial at 9600 baud (set in `setup()`).
- Move command: any string starting with `M` is parsed by extracting the token between the first and last comma as a 1-based servo id and the token after the last comma as angle (0–180). Example that works: `M,3,120` → moves servo id 3 (index 2) to 120°.
- Reserved literal commands: `SAVE` (append current pose to program buffer), `PLAY` (execute saved poses sequentially), `RESET` (smoothly move all servos to `HOME_POS` then clear saved program).
- Special mappings: servo index 5 (the 6th servo) remaps GUI 0–180 to a narrower real range via `map(ang, 0, 180, 3, 90)`. There is an unreachable/buggy branch checking `id == 7` — avoid changing protocol assumptions unless fixing that bug explicitly.

In-memory data & limits
- Program steps are stored in `int program[MAX_STEPS][NUM_SERVOS]` and tracked with `programLength`. Be cautious: on 8-bit Arduinos `int` is 2 bytes; increasing `MAX_STEPS` increases SRAM usage significantly.

Safety & modification guidelines for agents
- Do not change the serial baud or command keywords without checking the external GUI/host tools that communicate with the board.
- Avoid renumbering servos or changing the 1-based → 0-based conversion unless updating all callers. The code expects incoming ids to be 1-based and converts with `-1`.
- If improving the `M` parsing, maintain backward-compatible token extraction (first-to-last-comma id and last-token angle) or document a migration plan.

Developer workflows (how humans will run & test)
- Upload/build: open `arduino_code.ino` in the Arduino IDE (or use PlatformIO with an Arduino board target), select the correct board/port, and upload.
- Test via Serial Monitor: open serial monitor at 9600 baud and send commands. Example tests:
  - `M,1,90` — move servo 1 to 90°
  - `SAVE` — record pose
  - `PLAY` — play recorded poses
  - `RESET` — smooth home & clear buffer
- If you need logging, add `Serial.println()` statements — there is no existing logging framework.

Common patterns & notable quirks
- Smooth motion is implemented by incrementing/decrementing `currentPos[]` toward `targetPos[]` (or program step targets) one degree per loop, using `delay(STEP_DELAY)` to pace movement.
- `currentPos` and `targetPos` arrays are the authoritative runtime state; any change to servo output should update these arrays and write to the `Servo` object.
- Program uses blocking loops (while moving) for `RESET` and during `runProgram()`; careful if you add non-blocking features or background tasks.

Suggested safe improvements (explicitly labelled; only implement with tests)
- Replace `int` for stored positions with `uint8_t` to reduce memory usage on small MCUs (verify behaviour before/after).
- Fix the dead/unreachable `id == 7` branch (likely leftover) — either remove it or correct to intended index and update callers.
- Add explicit parser that returns errors over serial for malformed commands (keeps backward compatibility by accepting the current format).

Where to look when asked
- Movement & protocol: [arduino_code.ino](arduino_code.ino#L1).
- Pin mapping & constants: top of `arduino_code.ino` (lines ~1–30).

When in doubt, ask the user for:
- The type of Arduino board in use (Uno, Nano, Mega) because memory and pin mapping matter.
- Any external GUI or host script that communicates with the board (to validate command format) — do not change protocol without updating callers.

If you modify this file
- Run local verification with an Arduino board connected and exercise `M`, `SAVE`, `PLAY`, `RESET` manually in the Serial Monitor.

---
Please review any unclear parts (for example the exact `M` command token format used by your GUI) and tell me if you want me to (a) add automated tests in PlatformIO, (b) refactor parser, or (c) fix the `id == 7` bug now.
