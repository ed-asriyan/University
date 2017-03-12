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
const resetOptions = function () {
    mainCanvas.width = mainCanvas.parentNode.clientWidth;

    xOffsetInput.value = Math.round(mainCanvas.width / 2);
    yOffsetInput.value = Math.round(mainCanvas.height / 2);

    xScaleInput.value = 1;
    yScaleInput.value = 1;
    xScaleCenterInput.value = 0;
    yScaleCenterInput.value = 0;

    xRotationCenterInput.value = 0;
    yRotationCenterInput.value = 0;
    rotationInput.value = 0;
};

const reDraw = function () {
    let xOffset = parseInt(xOffsetInput.value);
    let yOffset = parseInt(yOffsetInput.value);

    let xScale = parseInt(xScaleInput.value);
    let yScale = parseInt(yScaleInput.value);

    return new Promise(() => {
        canvasManager.clear();

        canvasManager.offset = new Point(xOffset, yOffset);
        canvasManager.scale = new Point(xScale, yScale);

        canvasManager.drawGrid();
        for (let point of solver.allPointsSequence()) {
            canvasManager.drawPoint({
                point: point
            });
        }
    });
};


//
// XML elements initialization
//
resetOptions();
reDraw();


