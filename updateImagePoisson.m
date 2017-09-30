function out_im = updateImagePoisson(origIm, targetIm, w)
% origIm - input (content) RGB uint8 image
% targetIm - the stylized image to be process

%convert to LAB
origLAB = rgb2lab(origIm);
styledLAB = rgb2lab(targetIm);

%intialize
im_size = [size(targetIm,1),size(targetIm,2)];
out_im = styledLAB;


% loop over L,a,b channels, process eachone seperatly
% possible to change for with parfor to reproduce the times report in the
% paper
for c=1:3
    [dx, dy] = sGradMex(single(origLAB(:,:, c)));
    out_im(:,:,c) = doPoissonCombination(styledLAB(:,:,c),dx,dy,im_size,w(c));%test
end

%convert to rgb
out_im = im2uint8(lab2rgb(out_im));

end
