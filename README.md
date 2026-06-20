# JSIExample

Educational React Native project demonstrating manual JSI integration with a C++ `HostObject`.

## Requirements

- Node.js >= 20
- pnpm 10+
- Xcode (iOS) / Android Studio (Android)

## Getting Started

```bash
pnpm install
cd ios && pod install && cd ..
pnpm start
```

In another terminal:

```bash
pnpm ios
# or
pnpm android
```

## JSI Demo

On app launch, `JSIExampleInstaller.install()` runs automatically and registers `global.MathOperationsProxy`. Tap **All Math Operations** to exercise the native JSI bindings from JavaScript.

## Security

This project follows [npm-security-best-practices](https://github.com/lirantal/npm-security-best-practices):

- `pnpm-workspace.yaml`: `strictDepBuilds`, `blockExoticSubdeps`, `minimumReleaseAge`, `trustPolicy`
- `.npmrc`: `ignore-scripts=true`, `allow-git=none`, `node-linker=hoisted`
- CI uses `pnpm install --frozen-lockfile` and `pnpm audit`

### Controlled dependency upgrades

Avoid blind upgrades:

```bash
# Avoid
pnpm update
npx npm-check-updates -u

# Prefer
npx npm-check-updates --interactive
pnpm audit --fix
```

### CI-like install locally

```bash
pnpm install:ci
pnpm audit
```

## Scripts

| Script | Description |
|--------|-------------|
| `pnpm start` | Start Metro |
| `pnpm ios` | Run iOS app |
| `pnpm android` | Run Android app |
| `pnpm test` | Run Jest tests |
| `pnpm lint` | Run ESLint |
| `pnpm install:ci` | Deterministic install (frozen lockfile) |
| `pnpm audit` | Security audit |
