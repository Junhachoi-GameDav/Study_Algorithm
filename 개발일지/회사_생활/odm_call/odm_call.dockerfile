FROM python:latest
WORKDIR /app

VOLUME ["D:"]
RUN pip install --no-cache-dir requests

COPY odm_call.py .

CMD ["python", "odm_call.py"]