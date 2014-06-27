<div id="share-wrapper">
<ul class="share-inner-wrp">
        <!-- Facebook -->
        <?php if($variables['facebook']) : ?>
          <li class="facebook button-wrap"><a href="#">Facebook</a></li>
        <?php endif; ?>
        <!-- Twitter -->
        <?php if($variables['twitter']) : ?>
          <li class="twitter button-wrap"><a href="#">Tweet</a></li>
        <?php endif; ?>        
         <!-- Digg -->
        <?php if($variables['digg']) : ?>
          <li class="digg button-wrap"><a href="#">Digg it</a></li>
        <?php endif; ?>        
        <!-- Stumbleupon -->
        <?php if($variables['stumbleupon']) : ?>        
          <li class="stumbleupon button-wrap"><a href="#">Stumbleupon</a></li>
        <?php endif; ?>      
         <!-- Delicious -->
        <?php if($variables['delicious']) : ?>
          <li class="delicious button-wrap"><a href="#">Delicious</a></li>
        <?php endif; ?>        
        <!-- Google -->
        <?php if($variables['google']) : ?>
          <li class="google button-wrap"><a href="#">Plus Share</a></li>
        <?php endif; ?>        
    </ul>
</div>