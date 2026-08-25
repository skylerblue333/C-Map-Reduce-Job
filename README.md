# Sky Map Reduce Core

**Status: engineering beta.**

Sky Map Reduce Core is a dependency-free C11, **single-process** map/reduce-style word-frequency component. It maps bounded text inputs into normalized tokens and reduces equal tokens into deterministic counts.

## Implemented

- up to 256 input strings per operation
- up to 4 KiB per input string
- alphanumeric tokenization and lowercase normalization
- token length capped at 63 characters
- up to 1,024 unique tokens
- deterministic alphabetical output ordering
- count and lookup APIs through a reusable static C library
- strict warnings-as-errors builds
- deterministic CTest coverage
- AddressSanitizer and UndefinedBehaviorSanitizer verification
- non-root container packaging
- CLI truth signal: `distributed_execution=false`

## Build and verify

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
./build/sky_map_reduce_cli
```

## SKYCOIN4444 integration

This component can be embedded where small deterministic local text aggregation is useful—for example pre-processing bounded log, content, or analytics batches. Large workloads should use a separately implemented durable/distributed execution layer rather than treating this library as cluster infrastructure.

## Scope limitations

This is not Hadoop, Spark, distributed MapReduce, a scheduler, a worker pool, persistent batch storage, a shuffle service, streaming analytics, a fault-tolerant execution engine, or a production deployment. It performs one bounded aggregation operation in one process and keeps results only in caller-owned memory.

See `SECURITY.md` for input and resource boundaries.
