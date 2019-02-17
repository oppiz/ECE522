<?php
   $db = new SQLite3('/home/pi/ECE522/test.db');
   if(!$db) {
      echo $db->lastErrorMsg();
   } else {
      echo "Opened DATABASE!";
      $df1 = 0.0;
      $df2 = 0.0;
      
     
      $query = $db->prepare('SELECT MAX(ID), df1, df2 FROM PLCValues');
      //$query->bindParam(':df1', $df1, PDO::PARAM_STR);
      //$query->bindParam('df2', $df2, PDO::PARAM_STR);
      $results = $query->execute();
      while ($row = $results->fetchArray()) {
         echo "Temp: " . $row['df1'] . "\n";
         echo "Humid: " . $row['df2'] . "\n";
         echo "<br>";
      }

      if(isset($_POST['formWeather'])) {
         $expenses = $_POST['formWeather'];
         echo "ACTION!";
     }
      
      
   

      
   
   }
?>

<form id="form1" method="post">
 
<p>

Do you want the temp or humid?

<select name="formWeather">
  <option value="">Select...</option>
  <option value="T">Temp</option>
  <option value="H">Humid</option>
</select>

</p>

 
</form>