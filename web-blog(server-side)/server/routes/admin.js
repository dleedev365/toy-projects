const express = require('express');
const router = express.Router();
const Post = require('../models/Post');
const User = require('../models/User');
const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');

const adminLayout = '../views/layouts/admin';
const jwtSecret = process.env.JWT_SECRET;

const authMiddleWare = (req,res,next) => {
    const token = req.cookies.token;
   
    if(!token){
        return res.status(401).json({message: 'UnAuthorized'});
    }

    try{
        const decoded = jwt.verify(token, jwtSecret);
        req.userId = decoded.userId;
        next();
    }catch(error){
        res.status(401).json({message: "UnAuthorized"})
    }
};


router.get('/admin', async (req,res) => {
    try{
        const locals = {
            title: "Admin",
            description: "Simple Blog created with NodeJs, Express & MongoDB.",
        }

        res.render('admin/index', {locals, layout: adminLayout,    currentRoute: '/admin'});

    }catch(error){
        console.log(error);
    }
});

router.post('/admin', async (req,res) => {
    try{
        const {username, password} = req.body;
        const user = await User.findOne({ username});

        if (!user){
            return res.status(401).json({ message: "Invalid credentials"});
        }

        const isPasswordValid = await bcrypt.compare(password, user.password);

        if(!isPasswordValid){
            return res.status(401).json({message: "Invalid credentials" });
        }

        const token = jwt.sign({userId: user._id}, jwtSecret);
        res.cookie('token', token, {httpOnly: true});
        res.redirect('/dashboard');

    }catch(error){
        console.log(error);
    }
});

router.get('/dashboard', authMiddleWare,  async (req,res) => {
    try{
        const locals = {
            title: "Dashboard",
            description: 'Simple Blog created with NodeJS, Express & MongoDB',
            
        }
        const data = await Post.find();
        res.render('admin/dashboard',{
            locals, 
            data,
            layout: adminLayout,
            currentRoute: '/admin/dashboard'
        });
    }catch(error){
        console.log(error);
    }
    
});

router.get('/add-post', authMiddleWare,  async (req,res) => {
    try{
        const locals = {
            title: "Add Post",
            description: 'Simple Blog created with NodeJS, Express & MongoDB',
            
        }
        const data = await Post.find();
        res.render('admin/add-post',{
            locals, 
            data,
            layout: adminLayout,
            currentRoute: 'admin/add-post'
        });
    }catch(error){
        console.log(error);
    }
    
});

router.post('/add-post', authMiddleWare,  async (req,res) => {
    try{
        const {title, body} = req.body;
        
        try{
            const newPost = new Post({
                title,
                body
            });
            await Post.create(newPost);
            res.redirect("/dashboard");
        }catch(error){
            console.log(error);
        }
    }catch(error){
        console.log(error);
    }
    
});

router.get('/edit-post/:id', authMiddleWare,  async (req,res) => {
    try{
        let slug = req.params.id;
        const data = await Post.findOne({ _id: slug});
        res.render('admin/edit-post',{
            data,
            layout: adminLayout,
            currentRoute: `/edit-post/${slug}`
        });
    }catch(error){
        console.log(error);
    }
    
});

router.put('/edit-post/:id', authMiddleWare,  async (req,res) => {
    try{
        await Post.findByIdAndUpdate(req.params.id, {
            title: req.body.title,
            body: req.body.body,
            updatedAt: Date.now()
        });

        res.redirect(`/edit-post/${req.params.id}`);
    }catch(error){
        console.log(error);
    }
    
});

router.post('/register', async (req,res) => {
    try{
        const {username, password} = req.body;
        const hashedPassword = await bcrypt.hash(password, 10);

        try{
            const user = await User.create({username, password: hashedPassword});
            res.status(201).json({message: 'User Created', user});
        } catch(error){
            if(error.code == 11000){
                res.status(409).json({message: 'User Already In Use'})
            }
            res.status(500).json({message: 'Internal Server Error'});
        }

    }catch(error){
        console.log(error);
    }
});

router.delete('/delete-post/:id', authMiddleWare,  async (req,res) => {
    try{
        await Post.deleteOne({_id: req.params.id});
        res.redirect('/dashboard');
    }catch(error){
        console.log(error);
    }
    
});

router.get('/logout', (req, res) => {
    res.clearCookie('token');
    // res.json({message: "Logout Successful"});
    res.redirect('/', {
        currentRoute: '/admin/logout'
    });
});

module.exports = router;