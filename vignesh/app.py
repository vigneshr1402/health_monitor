from flask import Flask,redirect,render_template,request,url_for

app=Flask(__name__)

USER_DATA={
    "name":"test","password":"123"
}

@app.route('/')
def index():
    return render_template('login.html')

@app.route('/login',methods=['GET','POST'])
def login():
    if request.method=='POST':
        name=request.form["name"]
        pwd=request.form["pwd"]
        if name.lower()==USER_DATA["name"].lower() and pwd==USER_DATA["password"]:
            return redirect(url_for('details'), code=307)    
        return redirect('/')
    return redirect('/')

@app.route('/details',methods=['GET','POST'])
def details():
    if request.method=="POST":
        return render_template('index.html')
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True, host='localhost',port=8000)