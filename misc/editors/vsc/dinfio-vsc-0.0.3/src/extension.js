"use strict";

Object.defineProperty(exports, "__esModule", {value: true});
const vscode = require("vscode");

function activate(context) {
    const run = vscode.commands.registerCommand("dinfio.run", (fileUri) => {
        let terminal = vscode.window.activeTerminal;
        let file = (fileUri !== undefined) ? fileUri.path : vscode.window.activeTextEditor.document.uri.path;

        if (file.substring(0, 6) == "file://") file = file.substring(7);

        if (terminal === undefined) {
            terminal = vscode.window.createTerminal("Dinfio");
        }

        terminal.show(false);
        terminal.sendText("dinfio \"" + file + "\"");
    });

    const interactive = vscode.commands.registerCommand("dinfio.interactive", () => {
        let terminal = vscode.window.activeTerminal;
        
        if (terminal === undefined) {
            terminal = vscode.window.createTerminal("Dinfio");
        }

        terminal.show(false);
        terminal.sendText("dinfio");
    });

    context.subscriptions.push(run);
    context.subscriptions.push(interactive);
}

function deactivate() {}

exports.activate = activate;
exports.deactivate = deactivate;
