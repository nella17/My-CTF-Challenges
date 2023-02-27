<?php
error_reporting(0);
$file = $_GET['file'] ?? substr(urldecode($_SERVER['REQUEST_URI']),1);
if ($file == '') $file = 'welcome.php';
$list = Array(
    'Welcome' => '/welcome.php',
    'Get' => '/get.php',
    'Hint' => '/Dockerfile',
);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Box</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.0-beta1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-giJF6kkoqNQ00vy+HMDP7azOuL0xtbfIcaT9wjKHr8RbDVddVHyTfAAsrekwKmP1" crossorigin="anonymous">
    <style>
        html, body {
            height: 100%;
        }
        .container {
            min-height: calc(100% - 4rem);
        }
        .hint {
            font-size: 1px;
        }
    </style>
</head>
<body>
    <nav class="navbar navbar-expand-lg navbar-light bg-light justify-content-center">
        <a class="navbar-brand" href="/">Box</a>
        <ul class="navbar-nav">
            <?php foreach($list as $key => $value): ?>
                <li class="nav-item">
                    <a class="nav-link" href="<?= $value ?>"><?= $key ?></a>
                </li>
            <?php endforeach; ?>
        </ul>
    </nav>
    <div class="container d-flex align-items-center justify-content-center flex-column">
        <?php
            if (!(include $file))
                include_once '404.php';
        ?>
    </div>
    <span class="hint">FLAG at env</span>
</body>
</html>
