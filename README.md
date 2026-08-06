# MyFirstGame_Sabda

A third-person action game built with **Unreal Engine 5.4**, featuring a spell-casting combat system powered by the **Gameplay Ability System (GAS)**. Play as a necromancer wielding elemental abilities against AI-driven enemies in a dark fantasy setting.

---

## Table of Contents

- [Features](#features)
- [Screenshots](#screenshots)
- [Tech Stack](#tech-stack)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Gameplay Systems](#gameplay-systems)
  - [Ability System](#ability-system)
  - [Attribute Sets](#attribute-sets)
  - [AI System](#ai-system)
  - [UI / HUD](#ui--hud)
- [Controls](#controls)
- [Roadmap](#roadmap)
- [Known Issues](#known-issues)
- [Contributing](#contributing)
- [Acknowledgments](#acknowledgments)
- [License](#license)

---

## Features

- 🔥 **Fireball** — Projectile-based attack that can be cast from both hands
- 🌪️ **Tornado** — Area-of-effect wind ability with cooldown management
- ⚡ **Lightning Strike** — Powerful lightning attack with electrocute debuff
- 👻 **Ghost Walk** — Invisibility skill that cancels upon attacking
- 💀 **Death System** — Full death state handling for both player and enemies
- 🤖 **AI Enemies** — Behavior Tree-driven enemies with chase and melee combat
- 🎯 **HUD System** — Player health, mana, crosshair, enemy health bars, and spell cooldown display
- 🎮 **Enhanced Input** — Modern input system with Input Mapping Context

---

## Screenshots

<!-- Add screenshots of your game here -->
<!-- ![Gameplay Screenshot](Docs/screenshot_gameplay.png) -->

*Screenshots coming soon.*

---

## Tech Stack

| Component            | Technology                                |
|----------------------|-------------------------------------------|
| **Engine**           | Unreal Engine 5.4                         |
| **Language**         | C++ / Blueprints (Hybrid)                 |
| **Ability Framework**| Gameplay Ability System (GAS)             |
| **AI Framework**     | Behavior Trees + Blackboard               |
| **Input System**     | Enhanced Input System                     |
| **Version Control**  | Git + Git LFS                             |

---

## Project Structure

```
MyFirstGame_Sabda/
├── Config/                          # Engine & project configuration
│   ├── DefaultEngine.ini
│   ├── DefaultGame.ini
│   ├── DefaultGameplayTags.ini      # GAS gameplay tag definitions
│   └── DefaultInput.ini             # Input bindings
├── Content/
│   ├── AI/                          # AI controllers, behavior trees, blackboards
│   ├── Characters/
│   │   ├── Player/                  # Player blueprint & necromancer assets
│   │   └── Enemy/                   # Enemy blueprints (Ghoul, Ganfaul, etc.)
│   ├── GAS/
│   │   ├── Abilities/
│   │   │   ├── Player/              # Fireball, Tornado, Lightning, Ghost Walk
│   │   │   └── Enemy/               # Enemy melee ability
│   │   ├── Animations/              # Ability animation montages
│   │   └── Effects/                 # Gameplay effects (damage, cooldowns, stats)
│   ├── Input/                       # Enhanced Input actions & mapping context
│   ├── Maps/                        # Game levels
│   └── UI/                          # HUD widgets (health, mana, crosshair, etc.)
├── Source/MyFirstGame_Sabda/
│   ├── GAS_CharacterBase.h/.cpp     # Base character class with ASC integration
│   ├── AS_BaseStats.h/.cpp          # Shared attribute set (Health, MaxHealth, MoveSpeed)
│   ├── AS_Resource.h/.cpp           # Resource attributes (Mana, Stamina)
│   └── MyFirstGame_Sabda.Build.cs   # Module build configuration
└── MyFirstGame_Sabda.uproject       # Project descriptor
```

---

## Getting Started

### Prerequisites

- **Unreal Engine 5.4** (installed via Epic Games Launcher)
- **Visual Studio 2022** or **Xcode** (for C++ compilation)
- **Git LFS** — This project uses Git Large File Storage for binary assets

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/sabdaul-ulum/MyFirstGame_Sabda.git
   ```

2. **Initialize Git LFS:**
   ```bash
   cd MyFirstGame_Sabda
   git lfs install
   git lfs pull
   ```

3. **Generate project files:**
   - **Windows:** Right-click `MyFirstGame_Sabda.uproject` → *Generate Visual Studio project files*
   - **macOS:** Right-click `MyFirstGame_Sabda.uproject` → *Services* → *Generate Xcode Project*

4. **Open the project:**
   - Double-click `MyFirstGame_Sabda.uproject` to open in Unreal Editor
   - Or open through Epic Games Launcher

5. **Build and Play:**
   - Press `Ctrl+Shift+B` (Visual Studio) to build, or build directly in the Unreal Editor
   - Press **Play** in the editor to start the game

---

## Gameplay Systems

### Ability System

The project uses **Gameplay Ability System (GAS)** for all combat mechanics. All abilities are defined as `UGameplayAbility` subclasses (Blueprints) and activated via Gameplay Tags.

| Ability              | Tag                          | Type        | Cooldown Tag                   |
|----------------------|------------------------------|-------------|--------------------------------|
| Fireball             | `Ability.Attack.Fireball`    | Projectile  | —                              |
| Tornado              | `Ability.Attack.Tornado`     | AoE         | `Cooldown.Ability.Tornado`     |
| Lightning Strike     | `Ability.Attack.Lightning`   | Targeted    | `Cooldown.Ability.Lightning`   |
| Ghost Walk           | `Ability.GhostWalk`          | Buff/Stealth| `Cooldown.Ability.GhostWalk`   |
| Enemy Melee *(WIP)*  | *(Enemy only)*               | Melee       | `Cooldown.Ability.EnemyMelee`  |
| Death                | `Event.Death`                | State       | —                              |
| Electrocuted (Debuff)| `Event.Debuff.Electrocute`   | Debuff      | —                              |

### Attribute Sets

The project defines two C++ Attribute Sets:

- **`UAS_BaseStats`** — Shared between player and enemies: `Health`, `MaxHealth`, `MoveSpeed`
- **`UAS_Resource`** — Resource management: `Mana`, `MaxMana`, `Stamina`, `MaxStamina`

### AI System

> **🚧 Work in Progress** — AI currently supports basic melee combat. Future updates will enable enemies to cast their own spells and introduce boss encounters with unique ability sets.

Enemies use Unreal's **Behavior Tree** system with:
- `AIC_EnemyBase` — AI Controller
- `BT_EnemyLogic` — Main behavior tree
- `BB_EnemyMemory` — Blackboard for storing AI memory (e.g., player reference)
- `BTTask_ChasePlayer` — Custom task for player pursuit

### UI / HUD

| Widget               | Description                              |
|-----------------------|------------------------------------------|
| `WBP_MasterHUD`      | Root HUD container                       |
| `WBP_PlayerHUD`      | Player health and resource bars          |
| `WBP_PlayerSpell`    | Spell cooldown and ability slot display  |
| `WBP_EnemyHealth`    | Floating enemy health bar                |
| `WBP_Crosshair`      | Targeting crosshair                      |
| `WBP_GameOver`       | Game over screen                         |

---

## Controls

| Action               | Input                        |
|----------------------|------------------------------|
| Move                 | `W` `A` `S` `D`             |
| Look                 | Mouse                        |
| Jump                 | `Space`                      |
| Sprint               | `Shift`                      |
| Fireball             | Left Mouse Button (`LMB`)   |
| Ghost Walk           | `Q`                          |
| Tornado              | `E`                          |
| Lightning Strike     | `R`                          |

---

## Roadmap

### ⚔️ Combat & Abilities
- [ ] Expand melee combat system with combo chains and hit reactions
- [ ] Implement mana/stamina cost for abilities
- [ ] Add more player spells and ability upgrades
- [ ] Polish ability VFX and particle effects

### 🤖 AI & Enemies
- [ ] Enable AI enemies to cast spells (not just melee)
- [ ] Add boss encounters with unique ability sets
- [ ] Add more enemy types and encounter variety
- [ ] Improve AI behavior with patrol, flanking, and retreat states

### 🎒 Inventory System
- [ ] Implement core inventory framework
- [ ] Add consumable items: Health Potion, Mana Potion, Speed Potion
- [ ] Add passive items that grant player buffs (stat boosts, resistances)
- [ ] Create item pickup and drop mechanics
- [ ] Design inventory UI

### 🎮 General
- [ ] Implement a main menu
- [ ] Add sound effects and background music
- [ ] Create additional levels and environments
- [ ] Implement save/load system
- [ ] Remove deprecated `AS_PlayerStats` class

---

## Known Issues

- `AS_PlayerStats` is **deprecated** and will be removed in a future update. All stat logic has been migrated to `AS_BaseStats`.
- Enemy melee ability is a work in progress — hit reactions and combo systems are not yet implemented.
- AI enemies can only perform melee attacks; spell-casting AI is planned for future development.

---

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

---

## Acknowledgments

- [Epic Games](https://www.unrealengine.com/) — Unreal Engine 5.4
- [FAB (Unreal Engine Marketplace)](https://www.fab.com/) — All third-party assets used in this project are free assets sourced from FAB
- [Gameplay Ability System Documentation](https://docs.unrealengine.com/5.4/en-US/gameplay-ability-system-for-unreal-engine/) — Official GAS reference

---

## License

This project is for educational and personal use. All third-party assets (DreamscapeSeries, FXVarietyPack, character models, etc.) are free assets sourced from [FAB](https://www.fab.com/) (Unreal Engine Marketplace) and are subject to their respective license terms.

---

<p align="center">
  Built with ❤️ using Unreal Engine 5.4
</p>

