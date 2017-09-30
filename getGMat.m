function [Gx,Gy]=getGMat(w,h, mask)
imgSize=w*h;

dS=[1,-1];
filtSizeS=1;

indsGx1 = [];
indsGx2 = [];
valsGx = [];
indsGy1 = [];
indsGy2 = [];
valsGy = [];
mask_sw = mask(1:end - 1, :);
mask_sh = mask(:, 1: end - 1);

for disp=0:filtSizeS

  [X,Y] = meshgrid(1:w-1,1:h);
  indsGx1=[indsGx1; imIndexToVect(Y,X,h)];
  indsGx2=[indsGx2; imIndexToVect(Y,X+disp,h)];
  valsGx=[valsGx; mask_sh(:).*dS(disp+1)];
  
  [X,Y] = meshgrid(1:w,1:h-1);
  indsGy1=[indsGy1; imIndexToVect(Y,X,h)];
  indsGy2=[indsGy2; imIndexToVect(Y+disp,X,h)];
  valsGy=[valsGy; mask_sw(:).*dS(disp+1)];
  
end           

Gx=sparse(indsGx1,indsGx2,valsGx,imgSize,imgSize);
Gy=sparse(indsGy1,indsGy2,valsGy,imgSize,imgSize);

