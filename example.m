% EXAMPLE script for "Photorealistic Style Transfer with Screened Poisson
% Equation"
% Please cite: 
% Roey Mechrez, Eli Shechtman and Lihi Zelnik-Manor
% "Photorealistic Style Transfer with Screened Poisson Equation"
% BMVC 2017

grad_weight = [5,1,1];

images_numbers = [57,50,29];
% loop ocer 3 example images from different style transfer algorithms
% Neural style (Gatys et al., Luan et al.) + segmentation
% Style Swap Chen et al.
% and Neural style (Gatys et al.)
% see our paper for citations and details 
for im = 1:3
    i = images_numbers(im);
    % reading the pre-computed stylized images -- target_im
    switch im
        case 1%'gatys+segmentation'
            target_im = imread(sprintf('NSS%d.png',i));
            style_method = 'gatys with segmentation';
        case 2%'style_swap'
            target_im = imread(sprintf('SWAP%d.png',i));
            style_method = 'style_swap';
        case 3
            target_im = imread(sprintf('ns%d.png',i));
            style_method = 'neural style';
    end
    
    % reading the input and style images for display
    orig_im = imread(fullfile('input',sprintf('in%d.png',i)));
    style_im = imread(fullfile('style',sprintf('tar%d.png',i)));
    
    %  resize the images to have same size as target image
    if size(orig_im,1) ~= size(target_im,1) || size(orig_im,1) ~= size(style_im,1)
        [m,n,c] = size(target_im);
        orig_im = imresize(orig_im,[m,n]);
        style_im = imresize(style_im,[m,n]);
    end
    
    % compute our algorithm
    tic;
    out_im = updateImagePoisson(orig_im, target_im ,grad_weight);
    t = toc;
    fprintf('time to process image: %d is %2.2f sec \n',i,t);
    
    % save and print
    orig_im = myInsertText( orig_im, 'input' );
    style_im = myInsertText( style_im, 'style' );
    target_im = myInsertText( target_im, 'input' );
    out_im_tag = myInsertText( out_im, 'our SPE' ); 
    cat_im = cat(2,orig_im,style_im,target_im,out_im_tag);
    figure;imshow(cat_im);
    imwrite(out_im,fullfile('final',sprintf('out%d.png',i)));
end
