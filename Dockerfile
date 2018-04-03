# Debian openssh
#
# VERSION               0.3

FROM       debian:8
MAINTAINER Frankwai

ENV DEBIAN_FRONTEND noninteractive

# Install the base packages
RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get install -y inotify-tools git sudo make supervisor unzip zip wget pwgen apache2 libapache2-mod-php5 && \
    apt-get install -y php5 php5-curl php5-gd php5-json php5-mcrypt php5-mysql php5-readline php5-recode php-pear && \
    apt-get install -y mysql-server mysql-client
RUN apt-get clean

# Tweaks to give Apache/PHP write permissions to the app
RUN usermod -G staff www-data && \
    usermod -G staff mysql

# Add image configuration and scripts
ADD docker/start-apache2.sh /start-apache2.sh
ADD docker/start-mysqld.sh /start-mysqld.sh
ADD docker/run.sh /run.sh
ADD docker/create_mysql_users.sh /create_mysql_users.sh
RUN chmod 755 /*.sh
ADD docker/supervisord-apache2.conf /etc/supervisor/conf.d/supervisord-apache2.conf
ADD docker/supervisord-mysqld.conf /etc/supervisor/conf.d/supervisord-mysqld.conf
ADD docker/apache_default /etc/apache2/sites-enabled/000-default.conf

# Set PHP timezones to Europe/London
RUN sed -i "s/;date.timezone =/date.timezone = Europe\/London/g" /etc/php5/apache2/php.ini
RUN sed -i "s/;date.timezone =/date.timezone = Europe\/London/g" /etc/php5/cli/php.ini

# Install Camyks to /app
COPY engine/skeleton_site/ /app/
COPY engine /app/camyks/engine
COPY plugin /app/camyks/plugin
COPY Camyks.php.inc /app/camyks

COPY docker/site.php.inc /app/etc

RUN chown -R www-data:www-data /app/ ; \
    rm -Rf /var/lib/mysql/*

# Ensure we enable the modules for apache2
RUN a2enmod expires headers rewrite

# Add volumes for the camyks and MySql
VOLUME  ["/etc/mysql", "/var/lib/mysql" ,"/app" ]

EXPOSE 80 3306
CMD ["/run.sh"]
