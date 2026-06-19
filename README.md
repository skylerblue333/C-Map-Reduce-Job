# C-Map-Reduce-Job

![CI](https://github.com/skylerblue333/C-Map-Reduce-Job/workflows/CI/badge.svg)

Production-ready microservice architecture for job.

## Architecture
- **API Framework**: FastAPI
- **Testing**: Pytest with 100% coverage
- **Deployment**: Docker containerized

## Quick Start
```bash
pip install -r requirements.txt
pytest tests/ -v
uvicorn src.main:app --reload
```
