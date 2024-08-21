require('dotenv').config();

const express = require('express');
const expressLayout = require('express-ejs-layouts');
// allow HTTP verbs to be used where the client doesn't support it
const methodOverride = require('method-override');
const cookieParser = require('cookie-parser');
const connectDB = require('./server/config/db');
const MongoStore = require('connect-mongo');
const session = require('express-session');
const {isActiveRoute} = require('./server/helpers/routeHelpers');


const app = express();
const PORT = 3000 || process.env.PORT;

// connect to DB
connectDB();

// convert form data into json
app.use(express.urlencoded({extended: true}));
// convert the request body to JSON
app.use(express.json());
app.use(express.static('public'));
app.use(cookieParser());
app.use(methodOverride('_method'));

app.locals.isActiveRoute = isActiveRoute;

app.use(session({
    secret: 'keyboard cat',
    resave: false,
    saveUninitialized: true,
    store: MongoStore.create({
        mongoUrl: process.env.MONGODB_URL
    })
}));

// Templating Engine
app.use(expressLayout);
app.set('layout', './layouts/main');
app.set('view engine', 'ejs');


app.use('/', require('./server/routes/main'));
app.use('/', require('./server/routes/admin'));


app.listen(PORT, () => {
    console.log(`App listening on port ${PORT}`);
});