#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "pipeline_global.h"
#include <vector>
#include <complex>

using namespace std;

/**
 *Stores data in a share_ptr. Meant to pass data between Pipeline stages.
 */

namespace OSIP {
    template <class I>
    class Payload
    {
    public:
        /**
         * @brief Payload
         */
        Payload(vector<unsigned long> dim, shared_ptr<vector<I>> data);

        Payload(){ }

        ~Payload(){
            for(shared_ptr<vector<I>> p : _data){
                p = nullptr;
            }
            _dim.clear();
        }

        /**
         * @brief Payload Copy constructor, moves the shared points from the old object to the new object, thus deallocating the old one.
         * @param obj
         */
        Payload(const Payload &obj){
            this->_data = move(obj._data);
            this->_dim = move(obj._dim);
            this->vectorValid = obj.vectorValid;
        }

        /**
         * @brief operator = Equals operator, moves the shared points from the old object to the new object, thus deallocating the old one.
         * @param obj
         * @return
         */
        Payload& operator= (const Payload& obj){
            this->_data = move(obj._data);
            this->_dim = move(obj._dim);
            this->vectorValid = obj.vectorValid;
            return *this;
        }

        void addData(vector<unsigned long> dim, shared_ptr<vector<I>> data) {
            _dim.push_back(dim);
            _data.push_back(data);

            if(dim.size() > 0 && data){
                vectorValid = true;
            }else{
                vectorValid = false;
            }
        }

        /**
         * @brief getData Convenience function to get the first dataset
         * @return shared_ptr<I> at location 0
         */
        shared_ptr<vector<I>> getFirstData() { return _data.at(0); }

        /**
         * @brief getDimensions Convenience function to get the first dimensions
         * @return Dimensions of at location 0
         */
        vector<unsigned long> getFirstDimension() { return _dim.at(0); }

        /**
         * @brief getData Returns all shares_ptr<I> data stored in this Payload
         * @return Vector containing shared_ptr<I> values
         */
        vector<shared_ptr<vector<I>>> getData() { return _data; }

        /**
         * @brief getDimensions Returns all dimension vectors
         * @return a vector of dimensions
         */
        vector<vector<unsigned long>> getDimensions() { return _dim; }

        /**
         * @brief finished Deletes shared_ptr<I> references held by this Payload and clears the dimensions vector
         */
        void finished() {
            _data.clear();
            _dim.clear();
        }

        bool isValid() { return vectorValid; }
    private:
        /**
         * @brief _dim N Dimensions stored in a vector
         */
        vector<vector<unsigned long>> _dim;

        /**
         * @brief wrapped_data Data to send
         */
        vector<shared_ptr<vector<I>>> _data;

        /**
         * @brief vectorValid Quick flag to check if vector has been populated with anything
         */
        bool vectorValid = false;
    };
}

#endif // PAYLOAD_H
