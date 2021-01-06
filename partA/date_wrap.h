namespace mtm {
    class DateWrap 
    {
        private:
            int day=0;
            int month=0;
            int year=0;
        public:
            DateWrap(int day, int month, int year);
            int& day();
            int& month();
            int& year();
    };
}