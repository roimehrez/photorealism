function out_im = doPoissonCombination(im, im_dx, im_dy, im_size, grad_weight)
% optimization to solve SPE in order to combine
% L channel and the gradient channels
[h,w,~] = size(im);
meanL = mean2(im);
im = im - meanL;
TH = 100;

% remove very high gradients
im_dx(abs(im_dx) > TH) = 0;
im_dy(abs(im_dy) > TH) = 0;

% prepare the weights
weightGrad = grad_weight * ones(im_size);
weightColor = ones(im_size);

% sparse representation of the matries
[Gx,Gy] = getGMat(w,h,weightGrad);
n = size(Gx,1);
Icolor = sparse( 1:n, 1:n, weightColor(:));

% LTI system with each row as eq, combine the grad_x, grad_y and L
A = [Gx; Gy; Icolor];
b = double([weightGrad(:) .* im_dx(:); weightGrad(:) .* im_dy(:); im(:)]);

% solving
x = (A'*A) \ (A'*b);
out_im = reshape(x, [h,w]);
out_im = out_im + meanL;

