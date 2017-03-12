'use strict';

/**
 * Created by ed on 11.03.17.
 */

//
// XML elements
//
const mainCanvas = document.getElementById('mainCanvas');

const resetButton = document.getElementById('reset');
const redrawButton = document.getElementById('redraw');

const xMoveInput = document.getElementById('xMove');
const yMoveInput = document.getElementById('yMove');
const moveButton = document.getElementById('moveBtn');

const xScaleInput = document.getElementById('xScale');
const yScaleInput = document.getElementById('yScale');
const xScaleCenterInput = document.getElementById('xScaleCenter');
const yScaleCenterInput = document.getElementById('yScaleCenter');
const scaleButton = document.getElementById('scaleBtn');

const xRotationCenterInput = document.getElementById('xRotationCenter');
const yRotationCenterInput = document.getElementById('yRotationCenter');
const rotationInput = document.getElementById('rotation');
const rotationButton = document.getElementById('rotationBtn');

const canvasManager = new CanvasManager(mainCanvas);
const solver = new Solver(100);

//
// Functions
//
const reDraw = function () {
    canvasManager.clear();
    canvasManager.drawGrid();
    for (let point of solver.allPointsSequence()) {
        canvasManager.drawPoint({
            point: point
        });
    }
};

const resetImage = function () {
    mainCanvas.width = mainCanvas.parentNode.clientWidth;
    canvasManager.offset = {
        x: Math.round(mainCanvas.width / 2),
        y: Math.round(mainCanvas.height / 2)
    };

    canvasManager.scale = {
        x: 1,
        y: 1
    };
    // todo: reset rotation

    reDraw();
};

const resetOptions = function () {
    mainCanvas.height = 720;

    xMoveInput.value = 0;
    yMoveInput.value = 0;

    xScaleInput.value = 1;
    yScaleInput.value = 1;
    xScaleCenterInput.value = 0;
    yScaleCenterInput.value = 0;

    xRotationCenterInput.value = 0;
    yRotationCenterInput.value = 0;
    rotationInput.value = 0;
};

const moveImage = function (options = {x: 0, y: 0}) {
    canvasManager.offset = {
        x: canvasManager.offset.x + options.x,
        y: canvasManager.offset.y + options.y
    };
    reDraw();
};

const scaleImage = function (options = {x: 1, y: 1, center: new Point(0, 0)}) {
    canvasManager.scale = {
        x: canvasManager.scale.x * options.x,
        y: canvasManager.scale.y * options.y
    };
    canvasManager.scale.center = options.center;
    reDraw();
};

const rotateImage = function (options = {angle: 0, center: new Point(0, 0)}) {
    // todo: implement
};


//
// XML elements initialization
//
resetImage();
resetOptions();
reDraw();


