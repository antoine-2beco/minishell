./minishell | ls => ouvre readline
pipe n'execute pas les commandes tout a fait en parallele -> a cause du wait
export laisse passer des args sans = (ex: test)
unset segfault sur USER
seg fault si plus de path
seg fault si pas d'env (env -i) commande random apres un export
Makefile pas a la norme

CD :
OLDPWD doit etre unset au lancement

quand exec /bin/ls
definitely lost: 144 bytes in 1 blocks
leak lors de la commande d'apres

ctrl + C in a cat print two new lines

ctrl + \ in a cat don't print Quit : 3

