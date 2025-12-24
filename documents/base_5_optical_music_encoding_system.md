# Base 5 Optical Music Encoding System

| Value | Signal | Color |
| --- | --- | --- |
| `0` | All High | White |
| `1` | High R | Red |
| `2` | High G | Green |
| `3` | High B | Blue |
| `4` | All Low | Black |

---

## Paper Strip Layout

### Index 0 - 8: Instrument Instructions

| Index | Field |
| --- | --- |
| 0 | **Instrument 1** Opcode |
| 1 - 2 | **Instrument 1** Immediate |
| 3 | **Instrument 2** Opcode |
| 4 - 5 | **Instrument 2** Immediate |
| 6 | **Instrument 3** Opcode |
| 7 - 8 | **Instrument 3** Immediate |

### Index 9 - 15: Chord

| Index | Field |
| --- | --- |
| 9 - 10 | Extensions |
| 11 | Triad Quality |
| 12 - 13 | Root Note |
| 14 | Octave |
| 15 | Command Digit |

---

## Instrument Instruction Set

Format (Base 5): `[Opcode: 1 digit] [Immediate: 2 digits]`

| Name | Opcode | Description |
| --- | --- | --- |
| Play Note | 0 - 2 | `if(Immediate != 00) Play((Opcode * 25) + toDecimal(Immediate) + offset)` |
| Shift Positive | 3 | `Instrument = min(Instrument + Immediate, 127)` |
| Shift Negative | 4 | `Instrument = max(Instrument - Immediate, 0)` |

---

## Chord Instruction Set

Format (Base 5): `[Extension: 2 digits] [Triad: 1 digit] [Root: 2 digits] [Octave: 1 digit]` 

Behavior: Latched. State persists until new chord or mute (Octave == `4`) is received.

### Extensions

| Value | 7th Toggle | 9th Toggle | Power Toggle |
| --- | --- | --- | --- |
| `0` `0` |  |  |  |
| `0` `1` |  |  | On |
| `0` `2` |  | 9th |  |
| `0` `3` |  | 9th | On |
| `0` `4` |  | Flat |  |
| `1` `0` |  | Flat | On |
| `1` `1` | 7th |  |  |
| `1` `2` | 7th |  | On |
| `1` `3` | 7th | 9th |  |
| `1` `4` | 7th | 9th | On |
| `2` `0` | 7th | Flat |  |
| `2` `1` | 7th | Flat | On |
| `2` `2` | Major |  |  |
| `2` `3` | Major |  | On |
| `2` `4` | Major | 9th |  |
| `3` `0` | Major | 9th | On |
| `3` `1` | Major | Flat |  |
| `3` `2` | Major | Flat | On |

### Triad Quality

| Value | Quality |
| --- | --- |
| `0` | Major |
| `1` | Minor |
| `2` | Diminished |
| `3` | Augmented |
| `4` | Suspended 4 |

### Root Note

Special: `0` `0`: No-Op

| Value | Note (Octave 0) | Value | Note (Octave +1) |
| --- | --- | --- | --- |
| `0` `1` | C | `2` `3` | C |
| `0` `2` | C# | `2` `4` | C# |
| `0` `3` | D | `3` `0` | D |
| `0` `4` | D# | `3` `1` | D# |
| `1` `0` | E | `3` `2` | E |
| `1` `1` | F | `3` `3` | F |
| `1` `2` | F# | `3` `4` | F# |
| `1` `3` | G | `4` `0` | G |
| `1` `4` | G# | `4` `1` | G# |
| `2` `0` | A | `4` `2` | A |
| `2` `1` | A# | `4` `3` | A# |
| `2` `2` | B | `4` `4` | B |

### Octave

Special: `4`: Mute

| Value | Octave |
| --- | --- |
| `0` | 3 |
| `1` | 1 |
| `2` | 5 |
| `3` | 7 |