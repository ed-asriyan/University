'use strict';

/**
 * Created by ed on 11.03.17.
 */
class CanvasManager {
    constructor(canvas) {
        this._canvas = canvas;
        this._cameraOffset = {x: 0, y: 0};
    }

    set cameraOffset(options) {
        this._cameraOffset.x = options.x;
        this._cameraOffset.y = options.y;
    }

    get cameraOffset() {
        return {
            x: this._cameraOffset.x,
            y: this._cameraOffset.y
        };
    }

    moveCamera(options) {
        this._cameraOffset = {
            x: this._cameraOffset.x + options.x,
            y: this._cameraOffset.y + options.y
        }
    }

    getMousePosition(event) {
        if (event) {
            let rect = this._canvas.getBoundingClientRect();
            return this._toVirtualCoordinates({
                x: event.clientX - rect.left,
                y: event.clientY - rect.top
            });
        } else {
            return undefined;
        }
    }

    clear() {
        let context = this._canvas.getContext('2d');
        context.clearRect(0, 0, this._canvas.width, this._canvas.height);
    }

    drawLine(p1, p2, options = {}) {
        p1 = this._toScreenCoordinates(p1);
        p2 = this._toScreenCoordinates(p2);

        let context = this._canvas.getContext('2d');
        context.beginPath();

        context.lineWidth = options.lineWidth || 1;
        context.strokeOpacity = options.opacity || 1;
        context.strokeStyle = options.color || 'black';

        context.moveTo(p1.x, p1.y);
        context.lineTo(p2.x, p2.y);
        context.stroke();

        context.closePath();
    }

    drawPoint(options) {
        if (!options) return false;
        if (!options.point || !(isFinite(options.point.x) && isFinite(options.point.y))) return false;

        let point = options.point;
        if (!point) return false;
        let screenPoint = this._toScreenCoordinates(point);
        let x = screenPoint.x;
        let y = screenPoint.y;
        let color = options.color || 'black';
        let radius = options.radius || 1;

        let context = this._canvas.getContext("2d");

        context.beginPath();
        context.fillStyle = context.strokeStyle = color;
        context.arc(x, y, radius, 0, 2 * Math.PI);
        context.fill();
        context.closePath();

        return true;
    }

    drawGrid(options = {}) {
        options.color = options.color || 'gray';
        options.lineWidth = options.lineWidth || 1;
        options.axisWidth = options.axisWidth || 3;
        options.axisColor = options.axisColor || 'pink';
        options.step = options.step || 10;

        let top = this._toVirtualCoordinates({x: 0, y: 0});
        let bottom = this._toVirtualCoordinates({x: this._canvas.width, y: this._canvas.height});
        for (let x = Math.round(top.x / options.step) * options.step; x <= bottom.x; x += options.step) {
            this.drawLine(
                {x: x, y: top.y},
                {x: x, y: bottom.y},
                options
            );
        }

        for (let y = Math.round(top.y / options.step) * options.step; y <= bottom.y; y += options.step) {
            this.drawLine(
                {x: top.x, y: y},
                {x: bottom.x, y: y},
                options
            );
        }

        this.drawLine(
            top,
            {x: top.x, y: bottom.y},
            options
        );
        this.drawLine(
            top,
            {x: bottom.x, y: top.y},
            options
        );
        this.drawLine(
            {x: bottom.x, y: top.y},
            {x: bottom.x, y: bottom.y},
            options
        );
        this.drawLine(
            {x: top.x, y: bottom.y},
            {x: bottom.x, y: bottom.y},
            options
        );

        options.lineWidth = options.axisWidth;
        options.color = options.axisColor;
        this.drawLine(
            {x: top.x, y: 0},
            {x: bottom.x, y: 0},
            options
        );
        this.drawLine(
            {x: 0, y: top.y},
            {x: 0, y: bottom.y},
            options
        )
    }

    _toScreenCoordinates(point) {
        let result = new Point(point.x, point.y);

        result = transformations.move(result, this._cameraOffset);

        return result;
    }

    _toVirtualCoordinates(point) {
        let result = new Point(point.x, point.y);

        result = transformations.move(result, {
            x: -this._cameraOffset.x,
            y: -this._cameraOffset.y
        });

        return result;
    }
}