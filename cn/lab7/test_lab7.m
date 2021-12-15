format long;

noduri=[0 pi/6 pi/4 pi/3 pi/2];
val_functie=[0 1/2 sqrt(2)/2 sqrt(3)/2 1];
val_derivata=[1 sqrt(3)/2 sqrt(2)/2 1/2 0];
X=0:0.3:1.5;

[H, dH] = Hermite_interpolare(noduri, val_functie, val_derivata, X)
val_sin = sin(X)
val_cos = cos(X)
