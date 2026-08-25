# Security

Sky Map Reduce Core is an engineering-beta in-process aggregation library. It does not execute code from inputs, access files or networks, or provide a distributed execution boundary.

Inputs are bounded by count, text length, token length, and unique-token cardinality. Callers should still validate the provenance and sensitivity of text before processing it and avoid placing secrets into logs or examples.

The library is not a tenant isolation boundary and does not provide authentication, encryption, durable audit history, resource scheduling, sandboxing, or denial-of-service protection beyond its explicit local size bounds. A service wrapper should independently enforce request size, authentication/authorization, rate limits, timeouts, and process/container resource limits.

Report vulnerabilities privately through GitHub security reporting when available.
