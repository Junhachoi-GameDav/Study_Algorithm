FROM python:latest
WORKDIR /app

RUN pip install --no-cache-dir requests

COPY odm_call_eo.py .

CMD ["python", "odm_call_eo.py"]