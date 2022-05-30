const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>

<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script>
    function submitMessage() { //evia uma notificalção que a informação foi salva no esp com sucesso
      alert("Informação foi salva no esp");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }</script>
    <title>Hora Do Lanche</title>
    <style>
        body {
            font-family: Arial, Helvetica, sans-serif;
            background: linear-gradient(to right, rgb(29, 136, 207), rgb(110, 25, 143));
            text-align: center;
            color: #fff;
        }

        .container {
            position: absolute;
            top: 50%;
            left: 50%;
            transform: translate(-50%,-50%);
            width: 50%;
            background-color: rgba(0, 0, 0, 0.5);
            padding: 1em;
            border-radius: 10px;
        }

        button {
            background-color: slateblue;
            color: #fff;
            border: none;
            padding: 1em;
            border-radius: 10px;
            box-shadow: 1px 1px 6px black;
            cursor: pointer;
        }

            button:hover {
                background-color: steelblue;
            }

        .final-step,
        .second-step {
            display: none;
        }

        input {
            padding: 5px;
            border-radius: 5px;
            border: none;
            outline: none;
        }

        #resultado {
            font-size: 25px;
        }
    </style>
    <title>Bem vindo a HORA DO LANCHE</title>
</head>
<body>
<form action="/get" target="hidden-form">
    Horario atual: %inputIntH% <input type="number" name="inputIntH" min="0" max="23" maxlength="2" onkeypress="return (event.charCode !=8 && event.charCode ==0 || (event.charCode >= 48 && event.charCode <= 57))" >
    <input type="submit" value="Cadastrar" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    Minutos atual: %inputIntM% <input type="number" name="inputIntM" min="0" max="59" maxlength="2" onkeypress="return (event.charCode !=8 && event.charCode ==0 || (event.charCode >= 48 && event.charCode <= 57))">
    <input type="submit" value="Cadastrar" onclick="submitMessage()">
  </form>
  <iframe style="display:none" name="hidden-form"></iframe>

</body>
</html>
)=====";
