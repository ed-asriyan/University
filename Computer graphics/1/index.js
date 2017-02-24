'use strict';

/**
 * Created by ed on 19.02.17.
 */

const calcOrthocenter = function (p1, p2, p3) {
    let res;

    var a = p2.y - p1.y;
    var a1 = p2.x - p1.x;

    if (a != 0 && a1 != 0) {
        var ab = a / a1;
        var ab1 = -1 / ab;
        var ab2 = (p3.y) - (ab1 * p3.x);
    }

    var b = p3.y - p2.y;
    var b1 = p3.x - p2.x;

    if (b != 0 && b1 != 0) {
        var bc = b / b1;
        var bc1 = -1 / bc;
        var bc2 = (p1.y) - (bc1 * p1.x);
    }

    var c = p3.y - p1.y;
    var c1 = p3.x - p1.x;

    if (c != 0 && c1 != 0) {
        var ca = c / c1;
        var ca1 = -1 / ca;
        var ca2 = (p2.y) - (ca1 * p2.x);
    }

    if (a != 0 && a1 != 0 && b != 0 && b1 != 0 && c != 0 && c1 != 0) {
        var con = -bc1;
        var con1 = -bc2;
        var ad = con + ab1;
        var ad1 = ab2 + con1;
        var di = ad1 / ad;
        var di1 = -di;
        var y8 = (bc1 * di1) + bc2;

        if (Math.round(di1) == (di1) && Math.round(y8) == (y8)) {
            res = di1 + "," + y8;
        }
        else if (Math.round(di1) != (di1) && Math.round(y8) == (y8)) {
            res = di1.toFixed(5) + "," + y8;
        } else if (Math.round(di1) == (di1) && Math.round(y8) != (y8)) {
            res = di1 + "," + y8.toFixed(5);
        } else if (Math.round(di1) != (di1) && Math.round(y8) != (y8)) {
            res = di1.toFixed(5) + "," + y8.toFixed(5);
        }
    } else if (a != 0 && a1 != 0 && b != 0 && b1 != 0) {
        var con = -bc1;
        var con1 = -bc2;
        var ad = con + ab1;
        var ad1 = ab2 + con1;
        var di = ad1 / ad;
        var di1 = -di;
        var y8 = (bc1 * di1) + bc2;

        if (Math.round(di1) == (di1) && Math.round(y8) == (y8)) {
            res = di1 + "," + y8;
        } else if (Math.round(di1) != (di1) && Math.round(y8) == (y8)) {
            res = di1.toFixed(5) + "," + y8;
        } else if (Math.round(di1) == (di1) && Math.round(y8) != (y8)) {
            res = di1 + "," + y8.toFixed(5);
        } else if (Math.round(di1) != (di1) && Math.round(y8) != (y8)) {
            res = di1.toFixed(5) + "," + y8.toFixed(5);
        }
    } else if (b != 0 && b1 != 0 && c != 0 && c1 != 0) {
        var con2 = -ca1;
        var con3 = -ca2;
        var ad2 = con2 + bc1;
        var ad3 = bc2 + con3;
        var di = ad3 / ad2;
        var di1 = -di;
        var y8 = (ca1 * di1) + ca2;

        if (Math.round(di1) == (di1) && Math.round(y8) == (y8)) {
            res = di1 + "," + y8;
        } else if (Math.round(di1) != (di1) && Math.round(y8) == (y8)) {
            res = di1.toFixed(5) + "," + y8;
        } else if (Math.round(di1) == (di1) && Math.round(y8) != (y8)) {
            res = di1 + "," + y8.toFixed(5);
        } else if (Math.round(di1) != (di1) && Math.round(y8) != (y8)) {
            res = di1.toFixed(5) + "," + y8.toFixed(5);
        }
    } else if (a != 0 && a1 != 0 && c != 0 && c1 != 0) {
        var con2 = -ab1;
        var con3 = -ab2;
        var ad2 = con2 + ca1;
        var ad3 = ca2 + con3;
        var di = ad3 / ad2;
        var di1 = -di;
        var y8 = (ab1 * di1) + ab2;

        if (Math.round(di1) == (di1) && Math.round(y8) == (y8)) {
            res = di1 + "," + y8;
        } else if (Math.round(di1) != (di1) && Math.round(y8) == (y8)) {
            res = di1.toFixed(5) + "," + y8;
        } else if (Math.round(di1) == (di1) && Math.round(y8) != (y8)) {
            res = di1 + "," + y8.toFixed(5);
        } else if (Math.round(di1) != (di1) && Math.round(y8) != (y8)) {
            res = di1.toFixed(5) + "," + y8.toFixed(5);
        }
    }

    res = res.split(',');
    return {
        x: parseFloat(res[0]),
        y: parseFloat(res[1])
    };
};

const mainCanvas = document.getElementById('mainCanvas');
const mousePositionLabel = document.getElementById('mousePosition');

mainCanvas.height = mainCanvas.parentNode.clientHeight;
mainCanvas.width = mainCanvas.parentNode.clientWidth;

const canvasManager = new CanvasManager(mainCanvas);

const updatePointsList = function () {
    let pointsTable = document.getElementById('pointsList');

    // remove children
    while (pointsTable.firstChild) {
        pointsTable.removeChild(pointsTable.firstChild);
    }

    canvasManager.points.forEach(function (point, index) {
        let row = document.createElement('tr');
        row.point = point;

        // the first column
        let indexCol = document.createElement('td');
        let indexLabel = document.createElement('label');
        indexLabel.innerHTML = index.valueOf();
        indexCol.appendChild(indexLabel);
        row.appendChild(indexCol);

        // the second column
        let xCol = document.createElement('td');
        xCol.innerHTML = point.x.valueOf();
        row.appendChild(xCol);

        // the third column
        let yCol = document.createElement('td');
        yCol.innerHTML = point.y.valueOf();
        row.appendChild(yCol);

        // remove button
        let removeCol = document.createElement('td');
        let removeBtn = document.createElement('button');
        removeBtn.type = 'button';
        removeBtn.className = 'btn btn-danger';
        removeBtn.innerHTML = 'Remove';
        removeBtn.addEventListener('click', function () {
            // remove point from canvasManager
            canvasManager.points.splice(canvasManager.points.indexOf(this.parentNode.parentNode.point), 1);
            capture();
            canvasManager.reDraw();
        });
        row.addEventListener('mouseover', function () {
            this.point.radius = 4;
            this.point.color = 'red';
            canvasManager.reDraw();
        });
        row.addEventListener('mouseout', function () {
            canvasManager.points = historyManager.last();
            reDraw();
        });
        removeCol.appendChild(removeBtn);
        row.appendChild(removeCol);

        pointsTable.appendChild(row);
    });

    document.getElementById('pointsNumber').innerHTML = canvasManager.points.length
};

const historyManager = new HistoryManager(canvasManager.points);

const add = function () {
    let pointsInput = document.getElementById('pointsInput');
    let pos = pointsInput.value.split(',');
    let x = parseInt(pos[0]);
    let y = parseInt(pos[1]);
    if (x && y) {
        canvasManager.addPoint(x, y, 'black');
        capture();
        reDraw();
        pointsInput.value = '';
    }
};

const reDraw = function () {
    canvasManager.reDraw();
    updatePointsList();
};

const capture = function () {
    historyManager.capture(canvasManager.points);
};

const undo = function () {
    canvasManager.points = historyManager.undo();
    reDraw();
};

const redo = function () {
    canvasManager.points = historyManager.redo();
    reDraw();
};

const reset = function () {
    canvasManager.points = historyManager.reset();
    reDraw();
};

const clean = function () {
    canvasManager.points = historyManager.clear();
    reDraw();
};

mainCanvas.addEventListener('click', function (e) {
    let pos = canvasManager.getMousePosition(e);
    canvasManager.addPoint(pos.x, pos.y);
    capture();
    reDraw();
});

mainCanvas.addEventListener('mousemove', function (e) {
    let mousePosition = canvasManager.getMousePosition(e);

    mousePositionLabel.innerHTML = `Mouse position: ${mousePosition.x}, ${mousePosition.y}`;
    mousePositionLabel.style.visibility = 'visible';
});

mainCanvas.addEventListener('mouseleave', function (e) {
    mousePositionLabel.style.visibility = 'hidden';
});