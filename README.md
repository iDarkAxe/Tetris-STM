# Tetris_STM

# Présentation générale
Ce projet vise à créer notre propre version du célèbre jeu Tetris sur une carte STM32 L031K6. Pour atteindre cet objectif, l'équipe se concentrera sur l'intégration de cinq boutons essentiels pour l’expérience de jeu, ainsi que sur l'utilisation d'un écran OLED compact de 1,3 pouce.
Dans ce projet, nous avons pour but de recréer le jeu Tetris entièrement pour ce microcontrôleur et pour l’écran. La jouabilité et les règles sur le score et les niveaux sont similaires au jeu original. Les tetriminos (pièce de jeu) ont les formes originales du jeu.
La zone de jeu étant réduite due à la taille de l’écran, il faut se tenir assez près pour jouer. 

# Technologies utilisées
L’I2C est un bus informatique synchrone bidirectionnel qui permet l’intégration facile d’équipement compatible. Il était possible d’utiliser le SPI mais les performances de l’I2C dans son mode Fast Mode Plus à 1 MHz sont très satisfaisantes. 

# Pour réaliser ce projet nous voulons :
- Créer une zone de jeu 
-	Déplacer les pièces ainsi que les tourner au sein de la zone de jeu
-	Limiter les déplacements au sein de la zone de jeu
-	Supprimer les lignes complétées
- Avoir un système de :
    - Score
    - Niveau
	 - Difficulté
-	Arrêter le jeu quand la zone de jeu est pleine
-	Pouvoir relancer une partie lorsqu’elle s’est terminée
-	Avoir un jeu fluide sur lequel on puisse s’amuser
-	Documenter et maintenir un historique de versions de l’intégralité du code


# Contributeurs
Ce jeu de Tetris a entièrement été réalisé par Adrien Kerfriden, Lou Vacher et Pierre Pontet.

# Microcontrôleur concerné
Il a été conçu pour fonctionner sur une carte STM32 L031K6.

# Où brancher les boutons ?
Il suffit de brancher 5 boutons, sur les broches PA1, PA3, PA4, PA6 et PA7.
