# Gridless

> [!WARNING]
> Gridless is very much a work in progress. It should not be used for anything at this point because it lacks even basic functionality like saving files.
>
> **This project is not accepting pull requests at this time. Any external PRs will closed.**

Gridless is an interactive programming environment similar in concept to a spreadsheet, but with a radically different purpose and user interface. Gridless is designed to work with graphics, rather than tabular data.

## Proof of Concept
The following all applies to a minimal proof-of-concept version of Gridless.

The central component of the user interface is a freeform canvas (based on QGraphicsView), similar to that found in vector graphics tools.

For now, only two object types can be placed on the canvas:

- Point: Points mark positions on the canvas.
- View: Views provide a space for a formula written in JavaScript to draw on the canvas. The user only directly controls the position of the view. The size of the view depends on the content.

Every object has an ID that can be referenced by formulas. Each object ID must be a valid JavaScript identifier beginning with `$`. A default ID is generated, but can be changed by the user. Default IDs are compact. For instance the first Point object has the ID `$p1`, second has the ID `$p2`, and so on. Formulas are evaluated using `QJSEngine`.

### Drawing API

While formulas are written in plain JavaScript, I will use a TypeScript-style notation to describe the API. For this minimal proof-of-concept version, the API is very simple.

```typescript
// Points are relative to the position of the view. The coordinate system grows down and to the right. Negative coordinates are valid.
type Point = [number, number];

declare function line(p1: Point, p2: Point): void;

interface Obj {
    // Returns the point relative to the current view. The result changes depending on which formula is referencing the point.
    pos(): Point;
}

// For now, these subtypes do not add much, but this will change.
interface OPoint extends Obj { }
interface OView extends Obj {
    formula: string;
}
```

All object IDs are exposed in the global namespace as instances of a subtype of `Obj`.

Views expand to fit their contents, regardless of direction, but they have an origin point that remains stationary. This point shows up when the view is selected in the UI.

Formulas are supposed to be pure functions, although this isn't enforced. In the context of Gridless, this means they don't mutate the document. They still can produce their outputs via a transiently-impure API, but this impurity doesn't escape the formula, and the formula can be run multiple times producing the same result each time.

### Example

As it stands, Gridless isn't useful for much, so let's just draw a line with it. To do so, we create two point objects, keeping the default names `$p1` and `$p2`, then position them wherever we want.

We now create a view object. We can position this view anywhere on the canvas. It doesn't matter where we put it. The line will always be drawn in the same place because we're referencing point objects instead of hardcoded coordinates. We assign the view the following formula:

```javascript
line($p1.pos(), $p2.pos());
```

That's it!

### Sketch of the UI

```
┌─────┐
│  A  │
├─┬─┬─┤
│B│C│D│
└─└─┴─┘
```

- A: Main toolbar with file operations
- B: Tool chest with Select, Point, and View tools.
- C: The drawing canvas
- D: The inspector, allowing editing the properties of the selected object, which might include: ID, position, and/or formula.

## Extending the Proof of Concept

- Save/Load
- Undo/Redo
- SVG Export
- Print
- More object types:
    - Image: An image that can be referenced by formulas.
    - Input: Editable fields that can be used for user input, like text fields, dropdown menus, etc...
    - Path: A vector path that can be transformed by a formula.
    - Table: Tabular data, like a conventional spreadsheet. A formula can be assigned to this object to use it as an output.
- Hidden objects:
    - Some objects are only used for inputting information. Marking an object as hidden should make it show up with lower opacity. An Edit/View mode toggle is added to the UI. In View mode, hidden objects don't show up at all.
- Extended drawing API
- A custom programming language with purpose-built syntax.


## Build

```bash
mkdir -p build
cd build
# point CMake to your Qt6 installation if needed, e.g. -DCMAKE_PREFIX_PATH=/opt/Qt/6.5.1/gcc_64
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt6
cmake --build . --parallel
```

Run the produced executable `gridless` in the `build` directory.

## License
Copyright 2026 Sam Roth

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
