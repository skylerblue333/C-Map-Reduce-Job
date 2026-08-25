# Security

Sky Word Reducer is a local engineering-beta text-processing primitive.

The input file is capped at 1 MiB, individual tokens at 63 characters, and unique token cardinality at 1,024. The implementation checks read failures and count bounds, and CI executes strict warnings plus AddressSanitizer/UndefinedBehaviorSanitizer tests. The container runs a static binary as a non-root numeric user.

This component does not sandbox arbitrary file paths, process untrusted Unicode, provide authentication, encrypt data, isolate tenants, scan content, or implement distributed execution. Run it only with file access appropriate to the invoking process and do not treat it as a secure multi-tenant batch platform.
