'use strict';

/**
 * Created by ed on 18.02.17.
 */
class CanvasManager {
    constructor(canvas, options) {
        if (!options) {
            options = {}
        }

        this._canvas = canvas;
        this._historyManager = new HistoryManager();

        this._mousePositionLabal = document.createElement('label');
        this._mousePositionLabelVisibility = options.mousePositionLabelVisibility;
        this._mousePositionLabal.style.position = 'fixed';
        this._canvas.addEventListener('mouseleave', this._onMouseLeave.bind(this));
        this._canvas.addEventListener('mousemove', this._onMouseMove.bind(this));
        this._canvas.parentNode.appendChild(this._mousePositionLabal);

        this._gridVisibility = options.gridVisibility || true;
        this._gridStep = options.gridStep || 10;
        this._gridColor = options.gridColor || 'gray';
        this._gridOpacity = options.gridOpacity || 1;

        this._drawGrid();
        this.captureSource();
    }

    get mousePositionLabelVisibility() {
        return this._mousePositionLabelVisibility;
    }

    get gridVisibility() {
        return this._gridVisibility;
    }

    get gridStep() {
        return this._gridStep;
    }

    get gridColor() {
        return this._gridColor;
    }

    get gridOpacity() {
        return this._gridOpacity;
    }

    captureSource() {
        this._historyManager.capture(this._canvas.toDataURL());
    }

    undoSource() {
        let src = this._historyManager.undo();
        if (src) {
            this._applySource(src);
        }
        return src;
    }

    redoSource() {
        let src = this._historyManager.redo();
        if (src) {
            this._applySource(src);
        }
        return src;
    }

    getMousePosition(event) {
        if (event) {
            let rect = this._canvas.getBoundingClientRect();
            return {
                x: event.clientX - rect.left,
                y: event.clientY - rect.top
            };
        } else {
            return undefined;
        }
    }



    _applySource(src) {
        if (src) {
            let ctx = this._canvas.getContext('2d');
            let img = new Image();
            img.src = src;
            ctx.clearRect(0, 0, this._canvas.width, this._canvas.height);
            ctx.drawImage(img, 0, 0);
        }
    }

    _updateMousePositionLabel(event) {
        if (!this._mousePositionLabelVisibility) {
            return;
        }

        if (!event) {
            this._mousePositionLabal.style.display = 'none';
        } else {
            let mousePos = this.getMousePosition(event);
            if (mousePos === null) {
                this._mousePositionLabal.style.display = 'none';
            } else {
                let xPos = mousePos.x + 20;
                let yPos = mousePos.y + 25;

                this._mousePositionLabal.style.left = xPos + 'px';
                this._mousePositionLabal.style.top = yPos + 'px';

                this._mousePositionLabal.innerHTML = mousePos.x + ", " + mousePos.y;
                this._mousePositionLabal.style.display = 'inline';
            }
        }
    }

    _drawGrid() {
        if (!this._gridVisibility) {
            return;
        }

        let context = this._canvas.getContext("2d");
        for (let x = 0.5; x <= this._canvas.width; x += this._gridStep) {
            context.moveTo(x, 0);
            context.lineTo(x, this._canvas.height);
        }

        for (let y = 0.5; y <= this._canvas.height; y += this._gridStep) {
            context.moveTo(0, y);
            context.lineTo(this._canvas.width, y);
        }

        context.moveTo(this._canvas.width - 0.5, 0.5);
        context.lineTo(this._canvas.width - 0.5, this._canvas.height - 0.5);
        context.moveTo(0.5, this._canvas.height - 0.5);
        context.lineTo(this._canvas.width - 0.5, this._canvas.height - 0.5);

        context.strokeStyle = this._gridColor;
        context.globalAlpha = this._gridOpacity;
        context.stroke();

    }

    _onMouseMove(e) {
        this._updateMousePositionLabel(e);
    }

    _onMouseLeave(e) {
        this._updateMousePositionLabel(undefined);
    }
}