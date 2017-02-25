<!DOCTYPE html>
<html>
<title>W3.CSS</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="http://www.w3schools.com/lib/w3.css">
<link rel="stylesheet" href="http://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.4.0/css/font-awesome.min.css">
<body class="w3-container">
<body bgcolor="white">

<div class="w3-container w3-center w3-animate-top w3-teal ">
    <h1>Heart Disease Diagnosis</h1>
    <p>Get to know your heart better, with just one click!</p>
</div>

<style>

    #nav {
        line-height:30px;
        height:0px;
        width:0px;
        float:left;
        padding:30px;
    }

    section {
        width:700px;
        height:200px;
        float: right;
        padding:50px;
    }


</style>
<!DOCTYPE html>
<html>
<title>W3.CSS</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="http://www.w3schools.com/lib/w3.css">

<body>
<section>
    <div class="w3-card-4">
        <div class="w3-container w3-black w3-center w3-animate-opacity">
            <h2>Fill your Details</h2>
        </div>
        <form class="w3-form" action="?" method="POST">
            <div class="w3-input-group">
                <label class="w3-label w3-text-black"><b>Age</b></label>
                <input class="w3-input w3-border w3-dark-grey" name="age" type="text">
            </div>

            <div class="w3-input-group">
                <label class="w3-label w3-text-black"><b>Chest Pain Type</b></label>
                <input class="w3-input w3-border w3-dark-grey" name="cp" type="text">
            </div>
            <div class="w3-input-group">
                <label class="w3-label w3-text-black"><b>Resting Blood Pressure in mm Hg</b></label>
                <input class="w3-input w3-border w3-dark-grey" name="rest" type="text">
            </div>
            <div class="w3-input-group">
                <label class="w3-label w3-text-black"><b>Serum Cholestoral in mg/dl </b></label>
                <input class="w3-input w3-border w3-dark-grey" name="chol" type="text">


                <div class="w3-input-group">
                    <label class="w3-label w3-text-black"><b>Resting ECG result</b></label>
                    <input class="w3-input w3-border w3-dark-grey" name="erest" type="text">
                </div>
                <div class="w3-input-group">
                    <label class="w3-label w3-text-black"><b>Maximum Heart Rate </b></label>
                    <input class="w3-input w3-border w3-dark-grey" name="max" type="text">
                </div>

                <div class="w3-input-group">
                    <label class="w3-label w3-text-black"><b>ST Depression Induced by Exercise Relative to Rest </b></label>
                    <input class="w3-input w3-border w3-dark-grey" name="dep" type="text">
                </div>



                <div class="w3-input-group">
                    <label class="w3-label w3-text-black"><b>Number of major vessels colored by fluoroscopy </b></label>
                    <input class="w3-input w3-border w3-dark-grey" name="flouro" type="text">
                </div>

            </div>
            <div class="w3-input-group">
                <label class="w3-label w3-text-black"><b>Sex</b></label>
                <input type="radio" name="gender" value="0">&nbsp;Female &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="radio" name="gender" value="1">&nbsp;Male
            </div>
            <div class="w3-input-group ">
                <label class="w3-label w3-text-black"><b>Fasting Blood Sugar</b></label>
                <input type="radio" name="fast" value="1">&nbsp; >120mg/dl &nbsp;&nbsp;&nbsp;&nbsp;
                <input type="radio" name="fast" value="0">&nbsp; < 120mg/dl
            </div>
            <div class="w3-input-group">
                <label class="w3-label w3-text-black"><b>Heart Rate</b></label>
                <input type="radio" name="hr" value="3">&nbsp;Normal &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="radio" name="hr" value="6">&nbsp;Fixed Defect &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="radio" name="hr" value="7">&nbsp;Reversible Defect
            </div>
            <div class="w3-input-group ">
                <label class="w3-label w3-text-black"><b>Slope of peak exercise ST segment </b></label>
                <input type="radio" name="peak" value="1">&nbsp;Upsloping&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="radio" name="peak" value="2">&nbsp;Flat &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="radio" name="peak" value="3">&nbsp;Downsloping
            </div>
            <div class="w3-input-group">
                <label class="w3-label w3-text-black"><b>Exercise Induced Angina</b></label>
                <input type="radio" name="exea" value="1">&nbsp;YES &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input type="radio" name="exea" value="0">&nbsp;NO
            </div>

            <button  class="w3-btn w3-round-large w3-black w3-border w3-ripple ">Register</button>


        </form>
    </div>
</section>
<div id="nav">
    <img src ="https://cdn2.iconfinder.com/data/icons/medical-services/256/Diagnostic-512.png" height =" 1000px"  width="300px "
</div>
<form action="" method="POST">
    <?php
    if( isset($_POST["age"]) && isset($_POST["cp"]) && isset($_POST["rest"]) && isset($_POST["chol"]) && isset($_POST["erest"]) && isset($_POST["max"]) && isset($_POST["dep"]) && isset($_POST["flouro"]) && isset($_POST["gender"]) ) {
        $age = $_POST["age"];
        $cp = $_POST["cp"];
        $rest = $_POST["rest"];
        $chol = $_POST["chol"];
        $erest = $_POST["erest"];
        $max = $_POST["max"];
        $dep = $_POST["dep"];
        $flouro = $_POST["flouro"];
        $gender = $_POST["gender"];
        if ($gender == '0') {
            $gender = 0;
        } else {
            $gender = 1;
        }
        $fast = filter_input(INPUT_POST, $_POST["fast"]);
        if ($fast == '0') {
            $fast = 0;
        } else {
            $fast = 1;
        }
        $hr = filter_input(INPUT_POST, $_POST["hr"]);
        if ($hr == '3') {
            $gender = 3;
        } elseif ($hr == '6') {
            $hr = 6;
        } else {
            $hr = 7;
        }
        $peak = filter_input(INPUT_POST, $_POST["peak"]);
        if ($peak == '1') {
            $peak = 1;
        } elseif ($peak == '2') {
            $peak = 2;
        } else {
            $peak = 3;
        }
        $exea = filter_input(INPUT_POST, $_POST["exea"]);
        if ($exea == '0') {
            $exea = 1;
        } else {
            $exea = 1;
        }
        $myfile = fopen("testfile.txt", "w");
        fwrite($myfile, $age." ".$gender." ".$cp." ".$rest." ".$chol." ".$fast." ".$erest." ".$max." ".$exea." ".$dep." ".$peak." ".$flouro." ".$hr);
		fclose($myfile);
		exec("./a.out testfile.txt", $info);
        //info[0]
        HttpResponse::send(info[0]);
    }
    ?>
</form>
</body>
</html> 
