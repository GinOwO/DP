/*
// HTML Code Reference
// Navbar
<li class="nav-item">
<a href="#category-{}" class="nav-link">
<span class="nav-link-text">

</span>
</a>
</li>

// Contents to be shown
<div class="primary-category" id="category-{id}">
    <div class="category-div">
        <label class="category-title">{title}</label>
    </div>
    <ul class="accordion" id="accordion${id}">
        <li class="question" id="ID${id}">
            <input type="checkbox" name="quest" id="q${id}" onclick="toggleQuestion(this) />
            <label class="question-title" for="q${id}">
            ${title}
            </label>
            <div class="metatags" id="metatags-${id}">
                ${diff}${tags}
            </div>
            <div class="code-content">
                <div class="editor-container">
                    <div id="editor-${id}">

                    </div>
                </div>
            </div>
        </li>
    </ul>
</div>
*/

/**
 * @typedef {Object} Question
 * @typedef {Object} Category
 *
 * @property {Object<Question>} questions
 * @property {Object<Category>} categories
 * @property {string} buildDate
 * @property {Set<String>} openedQuestions
 * @property {string} theme
 * @property {string} pathPrefix
 * @property {string} mostRecent
 */

let questions = {};
let categories = {};
let buildDate = "";
let openedQuestions = new Set();
const theme = ["chaos", "xcode"][
    window.matchMedia("(prefers-color-scheme: light)").matches ? 1 : 0
];
let pathPrefix = "";
let mostRecent = "";
const badges = {
    Easy: `<img alt="Easy " src="https://img.shields.io/badge/Easy-ffff0f.svg?style=for-the-badge">`,
    Medium: `<img alt="Medium " src="https://img.shields.io/badge/Medium-ff8000.svg?style=for-the-badge">`,
    Hard: `<img alt="Hard " src="https://img.shields.io/badge/Hard-ff0000.svg?style=for-the-badge">`,

    Array: `<img alt="Array " src="https://img.shields.io/badge/Array-ffffff.svg?style=for-the-badge">`,
    String: `<img alt="String " src="https://img.shields.io/badge/String-429bff.svg?style=for-the-badge">`,
    Sorting: `<img alt="Sorting " src="https://img.shields.io/badge/-Sorting-fdc500.svg?style=for-the-badge">`,
    "Hash Table": `<img alt="Hash Table " src="https://img.shields.io/badge/-Hash%20Table-3454d1.svg?style=for-the-badge">`,
    "Two Pointers": `<img alt="Two Pointers " src="https://img.shields.io/badge/-Two%20Pointers-9b42ff.svg?style=for-the-badge">`,

    Tree: `<img alt="Tree " src="https://img.shields.io/badge/-Tree-2c6e49.svg?style=for-the-badge">`,
    "Binary Search": `<img alt="Binary Search " src="https://img.shields.io/badge/-Binary%20Search-ff9b42.svg?style=for-the-badge">`,
    "Binary Search Tree": `<img alt="Binary Search Tree " src="https://img.shields.io/badge/-Binary%20Search%20Tree-03440c.svg?style=for-the-badge">`,
    "Binary Indexed Tree": `<img alt="Binary Indexed Tree " src="https://img.shields.io/badge/-Binary%20Indexed%20Tree-058e3f.svg?style=for-the-badge">`,
    "Segment Tree": `<img alt="Segment Tree " src="https://img.shields.io/badge/-Segment%20Tree-04773b.svg?style=for-the-badge">`,

    "Depth-First Search": `<img alt="Depth First Search " src="https://img.shields.io/badge/-Depth--First%20Search-ffc9b9.svg?style=for-the-badge">`,
    "Breadth-First Search": `<img alt="Breadth First Search " src="https://img.shields.io/badge/-Breadth--First%20Search-ff9b42.svg?style=for-the-badge">`,

    Graph: `<img alt="Graph " src="https://img.shields.io/badge/-Graph-7a9b76.svg?style=for-the-badge">`,
    Recursion: `<img alt="Recursion " src="https://img.shields.io/badge/-Recursion-6dd6da.svg?style=for-the-badge">`,
    Backtracking: `<img alt="Backtracking " src="https://img.shields.io/badge/-Backtracking-ffeef2.svg?style=for-the-badge">`,
    "Dynamic Programming": `<img alt="Dynamic Programming " src="https://img.shields.io/badge/-Dynamic%20Programming-ff9b42.svg?style=for-the-badge">`,

    Math: `<img alt="Math " src="https://img.shields.io/badge/-Math-d1345b.svg?style=for-the-badge">`,
    Greedy: `<img alt="Greedy " src="https://img.shields.io/badge/-Greedy-ff92c2.svg?style=for-the-badge">`,
    Matrix: `<img alt="Matrix " src="https://img.shields.io/badge/-Matrix-ff42f5.svg?style=for-the-badge">`,
    Combinatorics: `<img alt="Combinatorics " src="https://img.shields.io/badge/-Combinatorics-4a5759.svg?style=for-the-badge">`,
    "Brute Force": `<img alt="Brute Force " src="https://img.shields.io/badge/-Brute%20Force-4a5759.svg?style=for-the-badge">`,
    "Eulerian Circuit": `<img alt="Eulerian Circuit " src="https://img.shields.io/badge/-Eulerian%20Circuit-780000.svg?style=for-the-badge">`,
    NLC: `<img alt="Non Leetcode " src="https://img.shields.io/badge/-Non%20Leetcode-71f45b.svg?style=for-the-badge">`,
};

/**
 * Hex for orange: #ff8000
 */

/**
 * Creates a category entry HTML
 *
 * @param {string} id
 * @param {string} title
 * @returns {string}
 */

function makeCategory(id, title) {
    if (title === "NLC") title = "Non Leetcode";
    return `
    <div class="primary-category" id="category-${id}">
    <div class="category-div">
    <label class="category-title">${title}</label>
    </div>
    <ul class="accordion" id="accordion${id}">
    </ul>
    </div>
    `;
}

/**
 * Creates a navbar entry HTML
 *
 * @param {string} id
 * @param {string} title
 * @returns {string}
 */

function makeNavbar(id, title) {
    if (title === "NLC") title = "Non Leetcode";
    return `
    <li class="nav-item">
        <a href="#category-${id}" class="nav-link">
            <span class="nav-link-text">
                ${title}
            </span>
        </a>
    </li>
    `;
}

/**
 * Creates a question entry HTML
 *
 * @param {string} id
 * @param {string} title
 * @param {string} diff
 * @param {Object<string>} tags
 * @returns {string}
 */

function makeQuestion(id, title, diff, tags) {
    return `
    <li class="question" id="ID-${id}">
        <input type="checkbox" name="quest" id="q${id}" onclick="toggleQuestion(this)" />
        <label class="question-title" for="q${id}">
            ${id}. ${title}
        </label>
        <div class="metatags" id="metatags-${id}">
            ${diff}${tags}
        </div>
        <div class="code-content">
            <div class="editor-container">
                <div class="editor-contents" id="editor-${id}">
                Loading...<br /> This will be done in a few seconds.<br />
                If you're seeing this for a long time something went wrong or poor connectivity!
                </div>
            </div>
        </div>
    </li>
    `;
}

/**
 * Load the questions and categories on DOM load
 * Also load the editor
 *
 * @returns {void}
 */

document.addEventListener("DOMContentLoaded", async () => {
    questions = await loadQuestions();
    categories = getCategories(questions);
    buildDate = questions["built on"].split(".")[0];

    createCategories();
    createQuestions();
});

/**
 * Load the questions from local source
 * 
 * This is what a single question looks like:
 * 
 * "id": {
        "Difficulty": "string",
        "Tags": [
            "string", "string", ....
        ],
        "Title": "string",
        "TitleSlug": "string",
        "URI": "./<category>/<filename>.cpp"
    }
 *
 * @returns {Promise<questions>}
 */

async function loadQuestions() {
    let response = await fetch("/URIs.json");
    if (!response.ok) {
        pathPrefix = "/" + window.location.href.split("/")[3] + "/";;
        response = await fetch(pathPrefix + "URIs.json");
        if (!response.ok) throw new Error("Network response was not ok");
    }

    const jsonData = await response.json(); // Extract JSON data from the response
    return jsonData;
}

/**
 * Gets the categories from the questions
 * Categories are the parent folders of the files
 *
 * This is what the return looks like:
 * {
 *   "category1": 0,
 *   "category2": 1,
 *   ....
 * }
 *
 *
 * @param {Object<Question>} questions
 * @returns {Object<Category>}
 */

function getCategories(questions) {
    let st = new Set();
    for (let key in questions) {
        if (key === "NLC" || key === "built on") continue;
        st.add(questions[key]["URI"].split("/")[1]);
    }
    let obj = {};
    let idx = 0;

    for (let category of st) {
        obj[category] = String(idx++);
    }
    obj["NLC"] = String(idx);
    return obj;
}

/**
 * Creates the categories on the DOM
 *
 * @returns {void}
 */

function createCategories() {
    let html = "",
        nv = "";
    for (let category in categories) {
        let c = ((str) => str.charAt(0).toUpperCase() + str.slice(1))(category);
        html += makeCategory(categories[category], c);
        nv += makeNavbar(categories[category], c);
    }
    nv += `<li class="nav-item" id="built-on">
    <a href="https://github.com/ginOwO/DP" class="nav-link">
    <span class="nav-link-text" id="github-url">Built On:<br />${buildDate}</span>
    </a>
    </li>`;
    document.getElementById("navbar").innerHTML += nv;
    document.getElementById("main-content").innerHTML += html;
}

/**
 * Creates the questions on the DOM
 *
 * @returns {void}
 */

function createQuestions() {
    let arr = [];
    for (let key in questions) {
        if (key !== "NLC" && key !== "built on") arr.push(key);
    }
    arr.sort((a, b) => Number(a) - Number(b));

    for (let key of arr) {
        let category = questions[key]["URI"].split("/")[1];
        let title = questions[key]["Title"];
        let diff = questions[key]["Difficulty"];
        let tags = questions[key]["Tags"]
            .map((tag) => {
                if (badges.hasOwnProperty(tag)) return badges[tag];
                return `<span class="tag">${tag}</span>`;
            })
            .join("");
        let html = makeQuestion(key, title, badges[diff], tags);
        document.getElementById(`accordion${categories[category]}`).innerHTML +=
            html;
    }

    let idx = 1;
    for (let obj of questions["NLC"]) {
        let category = "NLC";
        let key = idx++;
        let title = obj["Title"];
        let diff = "Medium";
        let tags = obj["Tags"];
        tags.push("NLC");
        let cat = obj["URI"].split("/")[1];
        tags.push(cat[0].toUpperCase() + cat.slice(1));
        tags = tags
            .map((tag) => {
                if (badges.hasOwnProperty(tag)) return badges[tag];
                tag.replace(" ", "%20");
                return `<img alt="${tag} " src="https://img.shields.io/badge/${tag}-000000.svg?style=for-the-badge">`;
            })
            .join("");
        let html = makeQuestion("N" + key, title, badges[diff], tags);
        document.getElementById(`accordion${categories[category]}`).innerHTML +=
            html;
    }
}

/**
 * Toggles the visibility of an accordion list item.
 *
 * @param {HTMLElement} obj
 * @returns {void}
 */

function toggleQuestion(obj) {
    let id = obj.id.slice(1);
    if (!openedQuestions.has(id)) {
        getCode(id).then((code) => setupEditor(id, code));
    }
    mostRecent = id;
}

/**
 * Setup the Ace editor
 *
 * @param {string} id
 * @param {string} code
 * @returns {void}
 */

function setupEditor(id, code) {
    let editor = ace.edit(`editor-${id}`);
    editor.setTheme(`ace/theme/${theme}`);
    editor.session.setMode("ace/mode/c_cpp");
    editor.session.setValue(code + "\n");
    openedQuestions[id] = editor;
    editor.setOption("readOnly", true);

    // Wrap text
    editor.session.setUseWrapMode(true);

    // Overscroll half
    editor.setOption("scrollPastEnd", 0.15);

    // Disable print margin
    editor.setShowPrintMargin(false);

    // Scroll down to opened content
    let element = document.getElementById(`editor-${id}`);
    if (element) {
        element.scrollIntoView({ behavior: "smooth", block: "start" });
    }
}

/**
 * Get the code from the URI
 *
 * @param {string} id
 * @returns {string}
 */

function getCode(id) {
    let uri = "";
    if (id[0] === "N") uri = questions["NLC"][Number(id.slice(1)) - 1]["URI"];
    else uri = questions[id]["URI"];
    if (pathPrefix !== "") uri = pathPrefix + uri.slice(1);
    return fetch(uri).then((res) => res.text());
}
