<?php
          $movie_query = "SELECT * FROM movies;";
          $results = mysqli_query($conn, $movie_query);
          if ($results) {
            echo "const movies = {";
            while ($row = mysqli_fetch_assoc($results)) {
              echo $row["number"].": {imbd_id:'".$row["imdb_id"]."', title:`".$row["original_title"]."`, genres:'".$row["genres"]."',";
              echo " overview:`".$row["overview"]."`.replace(/\uFFFD/g, ''), path:' ".$row["poster_path"]."', release: '".$row["release_date"]."', ";
              echo "runtime: '".$row["runtime"]."', vote: '".$row["vote_average"]."', count:'".$row["vote_count"]."',";
              echo "'},\n";
            }
            echo "};";
          }
 ?>
