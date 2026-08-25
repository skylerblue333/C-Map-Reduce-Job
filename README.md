# Sky Word Reducer

**Status: engineering beta.** A deterministic single-process C11 map/reduce demonstration for bounded word counting.

## Implemented

- Reads one local input file up to 1 MiB.
- Maps ASCII alphanumeric tokens to lowercase `(word, 1)` pairs.
- Reduces duplicate tokens into counts.
- Supports up to 1,024 unique words and 63 characters per word.
- Emits deterministic lexicographically sorted JSON counts.
- Strict C11 warnings-as-errors Release build and ASan/UBSan contract suite.
- Minimal static scratch container running as a non-root numeric user.

Example:

```bash
./app sample.txt
# {"total_words":5,"unique_words":3,"counts":{"alpha":2,"beta":2,"gamma":1}}
```

## Scope limitations

This is a **local educational/engineering primitive**, not a distributed MapReduce platform. It does not provide worker distribution, shuffle over a network, partition tolerance, retries, checkpoints, external object-store connectors, Unicode tokenization, streaming, HA, or production batch scheduling.

## SKYCOIN4444 integration

Use the deterministic reducer as a small native text-analysis primitive or reference implementation. Distributed scheduling, storage, observability, and production data-governance responsibilities remain external.
