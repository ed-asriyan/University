'use strict';

/**
 * Created by ed on 19.02.17.
 */

const body = document.getElementById('body');
const mainCanvas = document.getElementById('mainCanvas');
const mousePositionLabel = document.getElementById('mousePosition');
const pointList = document.getElementById('pointsList');
const pointsNumber = document.getElementById('pointsNumber');

mainCanvas.height = mainCanvas.parentNode.clientHeight;
mainCanvas.width = mainCanvas.parentNode.clientWidth;

const canvasManager = new CanvasManager(mainCanvas, {
    gridColor: 'gray',
    gridStep: 20,
});

const getCurrentHistoryState = function () {
    return {
        points: pointList.innerHTML,
        pointsNumber: pointsNumber.innerHTML,
        canvas: canvasManager.getImageData(),
    }
};

const setCurrentHistoryState = function (state) {
    if (state) {
        pointList.innerHTML = state.points;
        pointsNumber.innerHTML = state.pointsNumber;
        canvasManager.putImageData(state.canvas);
    }
};

const historyManager = new HistoryManager(getCurrentHistoryState());

const addPoint = function (x, y) {
    canvasManager.drawPoint(x, y, {
        width: 5,
        color: 'red'
    });

    let pointRow = document.createElement('tr');
    pointRow.className = '';
    pointRow.innerHTML = `<td>${pointList.childNodes.length + 1}</td><td>${x}</td><td>${y}</td>`;

    pointList.appendChild(pointRow);
    pointsNumber.innerHTML = pointList.childNodes.length - 1;

    historyManager.capture(getCurrentHistoryState());
};

const undoPoint = function () {
    setCurrentHistoryState(historyManager.undo());
};

const redoPoint = function () {
    setCurrentHistoryState(historyManager.redo());
};

const resetPoint = function () {
    setCurrentHistoryState(historyManager.reset());
};

const clearPoint = function () {
    setCurrentHistoryState(historyManager.clear());
};

mainCanvas.addEventListener('click', function (e) {
    let pos = canvasManager.getMousePosition(e);
    addPoint(pos.x, pos.y);
});

mainCanvas.addEventListener('mousemove', function (e) {
    let mousePosition = canvasManager.getMousePosition(e);

    mousePositionLabel.innerHTML = `Mouse position: ${mousePosition.x}, ${mousePosition.y}`;
    mousePositionLabel.style.visibility = 'visible';
});

mainCanvas.addEventListener('mouseleave', function (e) {
    mousePositionLabel.style.visibility = 'hidden';

});