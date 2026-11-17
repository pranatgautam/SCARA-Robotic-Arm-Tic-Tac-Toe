function result_matrix = processImage()
    clc, clear, close all

    % Load the image
    I = imread("file:///MATLAB Drive/superimpose/output_images3/image_ct_240_x_240__0260.bmp");

    % Define the grid size
    num_rows = 5;
    num_cols = 5;

    % Initialize the matrix to store the results
    result_matrix = cell(num_rows, num_cols);

    % Given coordinates, width, and height for each rectangle
    given_positions = [
        % x, y, width, height
        35, 35, 18, 18;   % Rectangle 1
        80, 35, 18, 18;   % Rectangle 2
        120, 35, 18, 18;
        165, 35, 18, 18;
        210, 35, 18, 18;
        35, 75, 18, 18;
        80, 75, 18, 18;
        120, 75, 18, 18;
        165, 75, 18, 18;
        210, 75, 18, 18;
        35, 120,18, 18;
        80, 120,18, 18;
        120, 120,18, 18;
        165, 120,18, 18;
        210, 120,18, 18;
        35, 162,18, 18;
        80, 162,18, 18;
        120, 162, 18, 18;
        165, 162, 18, 18;
        215, 162, 18, 18;
        35, 205,18, 18;
        80, 205,18, 18;
        120, 205,18, 18;
        165, 205,18, 18;
        215, 205,18, 18;
    ];

    % Define energy levels
    Renergy = 10;
    Genergy = 10;
    Benergy = 10;

    % Divide the image into 25 blocks and analyze each block
    for i = 1:size(given_positions, 1)
        % Get the coordinates of the current block
        x = given_positions(i, 1);
        y = given_positions(i, 2);
        width = given_positions(i, 3);
        height = given_positions(i, 4);

        % Extract the current block
        block = I(y:y+height-1, x:x+width-1, :);

        % Call tile2color function for each block
        color = tile2color(block, Renergy, Genergy, Benergy);

        % Store the result in the result matrix
        row_idx = ceil(i/num_cols); % Calculate the row index
        col_idx = mod(i-1, num_cols) + 1; % Calculate the column index
        result_matrix{row_idx, col_idx} = color;

        % Display the color-coded rectangle
        switch color
            case 'R'
                rectangle('Position', [x, y, width, height], 'EdgeColor', 'r', 'LineWidth', 2);
            case 'B'
                rectangle('Position', [x, y, width, height], 'EdgeColor', 'b', 'LineWidth', 2);
            case ' '
                rectangle('Position', [x, y, width, height], 'EdgeColor', 'g', 'LineWidth', 2);
        end
    end

    % Rotate result_matrix clockwise by 90 degrees
    result_matrix = rot90(result_matrix, -1);
    disp('Result Matrix Rotated 90 Degrees Clockwise:');
    disp(result_matrix);
end

% Define tile2color function
function color = tile2color(oneTile, Renergy, Genergy, Benergy)
    [no_pix_x, no_pix_y, ~] = size(oneTile);
    r = 0;
    b = 0;
    o = 0;
    for px = 1 : no_pix_x
        for py = 1 : no_pix_y
            if oneTile(px,py,1) > (oneTile(px, py, 2) + Genergy) && oneTile(px,py,1) > (oneTile(px,py,3) + Benergy)
                r = r + 1;
            elseif oneTile(px,py,3) > (oneTile(px, py, 1) + Renergy) && oneTile(px,py,3) > (oneTile(px,py,2) + Genergy)
                b = b + 1;
            else
                o = o + 1;
            end
        end
    end
    t = r + b + o;
    rp = r/t * 100;
    bp = b/t * 100;
    op = o/t * 100;
    if rp > 45
        color = 'R';
    elseif bp > 45
        color = 'B';
    else
        color = ' ';
    end
end
