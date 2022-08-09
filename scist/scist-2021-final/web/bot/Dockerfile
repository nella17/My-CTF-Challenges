# modify from https://github.com/splitline/My-CTF-Challenges/tree/master/ais3-pre-exam/2021/Web/xss-me/deploy/bot

FROM python:3.10

RUN apt update && \
    apt install -f -y --no-install-recommends chromium chromium-driver redis-server && \
    pip3 install selenium redis rq

COPY xssbot.py run.sh /
RUN useradd --no-create-home --home-dir / --shell /bin/false user

USER user
CMD /run.sh
