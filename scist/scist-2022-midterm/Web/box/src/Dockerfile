FROM php:8.0-apache

RUN a2enmod rewrite && sed -i '/\.ht"/,+2 s/^#*/#/' /etc/apache2/apache2.conf

COPY ./ /var/www/html/
