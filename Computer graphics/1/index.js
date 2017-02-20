'use strict';

/**
 * Created by ed on 19.02.17.
 */

const body = document.getElementById('body');
const mainCanvas = document.getElementById('mainCanvas');

mainCanvas.width = mainCanvas.parentNode.clientWidth;
mainCanvas.height = mainCanvas.parentNode.clientHeight;

const historyManager = new HistoryManager();

const canvasManager = new CanvasManager(mainCanvas, {
    mousePositionLabelVisibility: true,
    gridColor: 'gray',
    gridStep: 20,
});

mainCanvas.addEventListener('click', function (e) {
    let pos = canvasManager.getMousePosition(e);
    canvasManager.drawPoint(pos.x, pos.y, {
        width: 5,
        color: 'red'
    });
    canvasManager.captureSource();
});