import { useState, useEffect } from 'react';
import { useDispatch, useSelector } from 'react-redux';
import { Link } from 'react-router-dom';
import { toast } from 'react-toastify';
import Loader from '../Loader';
import { useNavigate } from 'react-router-dom';
import { setCredentials } from '../../slices/authSlice';
import { useRegisterMutation } from '../../slices/usersApiSlice';
import AnimatedContainerPage from '../pages/AnimatedContainerPage';

const RegisterScreen = ({ smallScreen }) => {
    const [user, setUser] = useState({
        name: '',
        email: '',
        password: '',
        verifyPassword: '',
    });

    const dispatch = useDispatch();
    const navigate = useNavigate();

    const { userInfo } = useSelector((state) => state.auth);

    const [register, { isLoading, isError, error }] = useRegisterMutation();

    useEffect(() => {
        if (userInfo) {
            navigate('/');
        }
    }, [navigate, userInfo]);

    const onChange = (e) =>
        setUser({ ...user, [e.target.name]: e.target.value });

    const onSubmit = async (e) => {
        e.preventDefault();
        if (user.password !== user.verifyPassword) {
            toast.error('Passwords do not match');
            return;
        } else {
            try {
                console.log(email)
                console.log(password)
                const res = await register({ name, email, password }).unwrap();
                dispatch(setCredentials({ ...res }));
                navigate('/');
            } catch (err) {
                toast.error(err?.data?.message || err.error);
            }
        }
    };

    return (
        <AnimatedContainerPage>
            <div className='container'>
                <div className='form-container form-centered'>
                    <h1>
                        <span className='text-primary'>Sign Up</span>
                    </h1>

                    <form onSubmit={onSubmit}>
                        <div className='form-group'>
                            <label htmlFor='name'>Name</label>
                            <input
                                type='text'
                                name='name'
                                className='form-input-text'
                                value={user.name}
                                onChange={onChange}
                                required
                            />

                            <label htmlFor='email'>Email Address</label>
                            <input
                                type='email'
                                name='email'
                                className='form-input-text'
                                value={user.email}
                                onChange={onChange}
                                required
                            />

                            <label htmlFor='password'>Password</label>
                            <input
                                type='password'
                                name='password'
                                className='form-input-text'
                                value={user.password}
                                onChange={onChange}
                                required
                                minLength='6'
                            />

                            <label htmlFor='verifyPassword'>
                                Confirm Password
                            </label>
                            <input
                                type='password'
                                name='verifyPassword'
                                className='form-input-text'
                                value={user.verifyPassword}
                                onChange={onChange}
                                required
                                minLength='6'
                            />

                            <div
                                className='form-group form-centered'
                                style={{
                                    padding: '1rem',
                                }}
                            >
                                <input
                                    type='submit'
                                    value='Register'
                                    className={
                                        smallScreen
                                            ? 'btn btn-big'
                                            : 'btn btn-dark'
                                    }
                                />

                                <p
                                    style={{
                                        padding: '0.6rem',
                                    }}
                                >
                                    Already a member?{' '}
                                    <Link to='/register'>Login</Link>
                                </p>
                            </div>
                        </div>
                    </form>
                </div>
            </div>
        </AnimatedContainerPage>
    );
};

export default RegisterScreen;
